#![allow(clippy::unwrap_used)]

//! Build the Rerun web-viewer .wasm and generate the .js bindings for it.

use std::time::Instant;

use anyhow::Context as _;
use cargo_metadata::camino::{Utf8Path, Utf8PathBuf};

pub fn workspace_root() -> Utf8PathBuf {
    cargo_metadata::MetadataCommand::new()
        .manifest_path(concat!(env!("CARGO_MANIFEST_DIR"), "/Cargo.toml"))
        .features(cargo_metadata::CargoOpt::NoDefaultFeatures)
        .no_deps()
        .exec()
        .unwrap()
        .workspace_root
}

pub fn default_build_dir() -> Utf8PathBuf {
    workspace_root().join("web_viewer")
}

fn target_directory() -> Utf8PathBuf {
    let metadata = cargo_metadata::MetadataCommand::new()
        .manifest_path(concat!(env!("CARGO_MANIFEST_DIR"), "/Cargo.toml"))
        .features(cargo_metadata::CargoOpt::NoDefaultFeatures)
        .exec()
        .unwrap();
    metadata.target_directory
}

#[derive(Clone, Copy, PartialEq, Eq)]
pub enum Profile {
    Release,
    Debug,
}

impl Profile {
    pub fn as_str(&self) -> &'static str {
        match self {
            Self::Release => "release",
            Self::Debug => "debug",
        }
    }
}

#[derive(Clone, Copy, PartialEq, Eq)]
pub enum Target {
    Browser,
    Module,

    /// Custom target meant for post-processing inside `rerun_js`.
    NoModulesBase,
}

impl argh::FromArgValue for Target {
    fn from_arg_value(value: &str) -> Result<Self, String> {
        match value {
            "browser" => Ok(Self::Browser),
            "module" => Ok(Self::Module),
            "no-modules-base" => Ok(Self::NoModulesBase),
            _ => Err(format!("Unknown target: {value}")),
        }
    }
}

/// Build `re_viewer` as Wasm, generate .js bindings for it, and place it all into the `build_dir` folder.
///
/// If `debug_symbols` is set, debug symbols are kept even in release builds,
/// allowing for better callstacks on panics, as well as in-browser profiling of the wasm.
pub fn build(
    profile: Profile,
    debug_symbols: bool,
    target: Target,
    build_dir: &Utf8Path,
    no_default_features: bool,
    features: &String,
) -> anyhow::Result<()> {
    std::env::set_current_dir(workspace_root())?;

    eprintln!("Building web viewer…\n");

    let crate_name = "re_viewer";

    // Where we tell cargo to build to.
    // We want this to be different from the default target folder
    // in order to support recursive cargo builds (calling `cargo` from within a `build.rs`).
    let target_wasm_dir = Utf8PathBuf::from(format!("{}_wasm", target_directory()));

    // Repository root
    let root_dir = target_wasm_dir.parent().unwrap();

    // Where we will place the final .wasm and .js artifacts.
    assert!(
        build_dir.exists(),
        "Failed to find dir {build_dir}. CWD: {:?}, CARGO_MANIFEST_DIR: {:?}",
        std::env::current_dir(),
        std::env!("CARGO_MANIFEST_DIR")
    );

    // The two files we are building:
    let wasm_path = build_dir.join(format!("{crate_name}_bg.wasm"));
    let js_path = build_dir.join(format!("{crate_name}.js"));

    // Clean old versions:
    std::fs::remove_file(wasm_path.clone()).ok();
    std::fs::remove_file(js_path).ok();

    {
        eprintln!("Compiling Rust to wasm in {target_wasm_dir}…");
        let start_time = Instant::now();

        let mut cmd = std::process::Command::new("cargo");
        cmd.args([
            "build",
            "--quiet",
            &format!("--package={crate_name}"),
            "--lib",
            "--target=wasm32-unknown-unknown",
            &format!("--target-dir={}", target_wasm_dir.as_str()),
        ]);
        if no_default_features {
            cmd.arg("--no-default-features");
        }
        if !features.is_empty() {
            cmd.arg(&format!("--features={features}"));
        }
        if profile == Profile::Release {
            cmd.arg("--release");
        }

        // This is required for unstable WebGPU apis to work
        // https://rustwasm.github.io/docs/wasm-bindgen/web-sys/unstable-apis.html
        cmd.env("RUSTFLAGS", "--cfg=web_sys_unstable_apis");

        // When executing this script from a Rust build script, do _not_, under any circumstances,
        // allow pre-encoded `RUSTFLAGS` to leak into the current environment.
        // These pre-encoded flags are generally generated by Cargo itself when loading its
        // configuration from e.g. `$CARGO_HOME/config.toml`; which means they will contain
        // values that only make sense for the native target host, not for a wasm build.
        cmd.env("CARGO_ENCODED_RUSTFLAGS", "--cfg=web_sys_unstable_apis");

        eprintln!("{root_dir}> {cmd:?}");
        let status = cmd
            .current_dir(root_dir)
            .status()
            .context("Failed to build Wasm")?;

        anyhow::ensure!(status.success(), "Failed to build Wasm");

        eprintln!(
            "Web viewer .wasm built in {:.1}s\n",
            start_time.elapsed().as_secs_f32()
        );
    }

    {
        eprintln!("Generating JS bindings for wasm…");
        let start_time = Instant::now();

        let build = profile.as_str();

        let target_wasm_path = target_wasm_dir
            .join("wasm32-unknown-unknown")
            .join(build)
            .join(format!("{crate_name}.wasm"));

        let mut bindgen_cmd = wasm_bindgen_cli_support::Bindgen::new();
        bindgen_cmd
            .input_path(target_wasm_path.as_str())
            .out_name(crate_name);
        match target {
            Target::Browser => bindgen_cmd.no_modules(true)?.typescript(false),
            Target::Module => bindgen_cmd.no_modules(false)?.typescript(true),
            Target::NoModulesBase => bindgen_cmd
                .no_modules(true)?
                .reference_types(true)
                .typescript(true),
        };
        if let Err(err) = bindgen_cmd.generate(build_dir.as_str()) {
            if err
                .to_string()
                .starts_with("cannot import from modules (`env`")
            {
                // Very common error: "cannot import from modules (`env`) with `--no-modules`"
                anyhow::bail!(
                "Failed to run wasm-bindgen: {err}. This is often because some dependency is calling `std::time::Instant::now()` or similar. You can try diagnosing this with:\n\
                wasm2wat {target_wasm_path} | rg '\"env\"'\n\
                wasm2wat {target_wasm_path} | rg 'call .now\\b' -B 20\n\
                \n\
                You can also try https://rustwasm.github.io/twiggy/usage/command-line-interface/paths.html#twiggy-paths
                "
            );
            } else {
                return Err(err.context("Failed to run wasm-bindgen"));
            }
        }

        eprintln!(
            "Generated JS bindings in {:.1}s\n",
            start_time.elapsed().as_secs_f32()
        );
    }

    if profile == Profile::Release {
        eprintln!("Optimizing wasm with wasm-opt…");
        let start_time = Instant::now();

        // to get wasm-opt:  apt/brew/dnf install binaryen
        let mut cmd = std::process::Command::new("wasm-opt");

        let mut args = vec![
            wasm_path.as_str(),
            "-O2",
            "--output",
            wasm_path.as_str(),
            "--enable-reference-types",
        ];
        if debug_symbols {
            args.push("-g");
        }
        cmd.args(args);
        eprintln!("{root_dir}> {cmd:?}");

        let output = cmd
            .current_dir(root_dir)
            .output()
            .context("Failed to run wasm-opt, it may not be installed")?;

        anyhow::ensure!(
            output.status.success(),
            "Failed to run wasm-opt:\n{}",
            String::from_utf8_lossy(&output.stderr),
        );

        eprintln!(
            "Optimized wasm in {:.1}s\n",
            start_time.elapsed().as_secs_f32()
        );
    }

    // --------------------------------------------------------------------------------

    eprintln!("Finished {wasm_path}");

    Ok(())
}
