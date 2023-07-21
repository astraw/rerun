// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/testing/components/fuzzy.fbs"

#pragma once

#include "../datatypes/affix_fuzzer1.hpp"

#include <cstdint>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace arrow {
    class DataType;
}

namespace rr {
    namespace components {
        struct AffixFuzzer7 {
            std::optional<std::vector<rr::datatypes::AffixFuzzer1>> many_optional;

          public:
            AffixFuzzer7(std::optional<std::vector<rr::datatypes::AffixFuzzer1>> many_optional)
                : many_optional(std::move(many_optional)) {}

            /// Returns the arrow data type this type corresponds to.
            static std::shared_ptr<arrow::DataType> to_arrow_datatype();
        };
    } // namespace components
} // namespace rr
