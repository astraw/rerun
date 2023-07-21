// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/testing/components/fuzzy.fbs"

#include "affix_fuzzer14.hpp"

#include "../datatypes/affix_fuzzer1.hpp"

#include <arrow/api.h>

namespace rr {
    namespace components {
        std::shared_ptr<arrow::DataType> AffixFuzzer14::to_arrow_datatype() {
            return arrow::dense_union({
                arrow::field("_null_markers", arrow::null(), true, nullptr),
                arrow::field("degrees", arrow::float32(), false, nullptr),
                arrow::field("radians", arrow::float32(), false, nullptr),
                arrow::field(
                    "craziness",
                    arrow::list(arrow::field(
                        "item", rr::datatypes::AffixFuzzer1::to_arrow_datatype(), false, nullptr)),
                    false,
                    nullptr),
                arrow::field("fixed_size_shenanigans",
                             arrow::fixed_size_list(
                                 arrow::field("item", arrow::float32(), false, nullptr), 3),
                             false,
                             nullptr),
            });
        }
    } // namespace components
} // namespace rr
