// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/testing/components/fuzzy.fbs"

#include "affix_fuzzer13.hpp"

#include <arrow/api.h>

namespace rr {
    namespace components {
        std::shared_ptr<arrow::DataType> AffixFuzzer13::to_arrow_datatype() {
            return arrow::list(arrow::field("item", arrow::utf8(), true, nullptr));
        }
    } // namespace components
} // namespace rr
