// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/testing/components/fuzzy.fbs"

#pragma once

#include <arrow/type_fwd.h>
#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

namespace rr {
    namespace components {
        struct AffixFuzzer11 {
            std::optional<std::vector<float>> many_floats_optional;

          public:
            AffixFuzzer11(std::optional<std::vector<float>> many_floats_optional)
                : many_floats_optional(std::move(many_floats_optional)) {}

            /// Returns the arrow data type this type corresponds to.
            static std::shared_ptr<arrow::DataType> to_arrow_datatype();

            /// Creates a new array builder with an array of this type.
            static arrow::Result<std::shared_ptr<arrow::ListBuilder>> new_arrow_array_builder(
                arrow::MemoryPool* memory_pool
            );

            /// Fills an arrow array builder with an array of this type.
            static arrow::Status fill_arrow_array_builder(
                arrow::ListBuilder* builder, const AffixFuzzer11* elements, size_t num_elements
            );
        };
    } // namespace components
} // namespace rr
