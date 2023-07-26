// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/testing/components/fuzzy.fbs"

#pragma once

#include "../datatypes/affix_fuzzer3.hpp"

#include <arrow/type_fwd.h>
#include <cstdint>
#include <utility>
#include <vector>

namespace rr {
    namespace components {
        struct AffixFuzzer16 {
            std::vector<rr::datatypes::AffixFuzzer3> many_required_unions;

          public:
            AffixFuzzer16(std::vector<rr::datatypes::AffixFuzzer3> many_required_unions)
                : many_required_unions(std::move(many_required_unions)) {}

            /// Returns the arrow data type this type corresponds to.
            static std::shared_ptr<arrow::DataType> to_arrow_datatype();

            /// Creates a new array builder with an array of this type.
            static arrow::Result<std::shared_ptr<arrow::ListBuilder>> new_arrow_array_builder(
                arrow::MemoryPool* memory_pool
            );

            /// Fills an arrow array builder with an array of this type.
            static arrow::Status fill_arrow_array_builder(
                arrow::ListBuilder* builder, const AffixFuzzer16* elements, size_t num_elements
            );
        };
    } // namespace components
} // namespace rr
