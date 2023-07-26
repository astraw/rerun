// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/testing/datatypes/fuzzy.fbs"

#pragma once

#include <arrow/type_fwd.h>
#include <cstdint>
#include <optional>
#include <utility>

namespace rr {
    namespace datatypes {
        struct AffixFuzzer2 {
            std::optional<float> single_float_optional;

          public:
            AffixFuzzer2(std::optional<float> single_float_optional)
                : single_float_optional(std::move(single_float_optional)) {}

            /// Returns the arrow data type this type corresponds to.
            static std::shared_ptr<arrow::DataType> to_arrow_datatype();

            /// Creates a new array builder with an array of this type.
            static arrow::Result<std::shared_ptr<arrow::FloatBuilder>> new_arrow_array_builder(
                arrow::MemoryPool* memory_pool
            );

            /// Fills an arrow array builder with an array of this type.
            static arrow::Status fill_arrow_array_builder(
                arrow::FloatBuilder* builder, const AffixFuzzer2* elements, size_t num_elements
            );
        };
    } // namespace datatypes
} // namespace rr
