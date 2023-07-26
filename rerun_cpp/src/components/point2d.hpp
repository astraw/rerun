// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/components/point2d.fbs"

#pragma once

#include "../datatypes/point2d.hpp"

#include <arrow/type_fwd.h>
#include <cstdint>
#include <utility>

namespace rr {
    namespace components {
        /// A point in 2D space.
        struct Point2D {
            rr::datatypes::Point2D xy;

          public:
            Point2D(rr::datatypes::Point2D xy) : xy(std::move(xy)) {}

            /// Returns the arrow data type this type corresponds to.
            static std::shared_ptr<arrow::DataType> to_arrow_datatype();

            /// Creates a new array builder with an array of this type.
            static arrow::Result<std::shared_ptr<arrow::StructBuilder>> new_arrow_array_builder(
                arrow::MemoryPool* memory_pool
            );

            /// Fills an arrow array builder with an array of this type.
            static arrow::Status fill_arrow_array_builder(
                arrow::StructBuilder* builder, const Point2D* elements, size_t num_elements
            );
        };
    } // namespace components
} // namespace rr
