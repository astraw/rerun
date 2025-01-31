// DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/store/re_types/definitions/rerun/blueprint/components/space_view_class.fbs".

#pragma once

#include "../../component_descriptor.hpp"
#include "../../datatypes/utf8.hpp"
#include "../../result.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

namespace rerun::blueprint::components {
    /// **Component**: The class identifier of view, e.g. `"2D"`, `"TextLog"`, ….
    struct SpaceViewClass {
        rerun::datatypes::Utf8 value;

      public:
        SpaceViewClass() = default;

        SpaceViewClass(rerun::datatypes::Utf8 value_) : value(std::move(value_)) {}

        SpaceViewClass& operator=(rerun::datatypes::Utf8 value_) {
            value = std::move(value_);
            return *this;
        }

        SpaceViewClass(std::string value_) : value(std::move(value_)) {}

        SpaceViewClass& operator=(std::string value_) {
            value = std::move(value_);
            return *this;
        }

        /// Cast to the underlying Utf8 datatype
        operator rerun::datatypes::Utf8() const {
            return value;
        }
    };
} // namespace rerun::blueprint::components

namespace rerun {
    static_assert(sizeof(rerun::datatypes::Utf8) == sizeof(blueprint::components::SpaceViewClass));

    /// \private
    template <>
    struct Loggable<blueprint::components::SpaceViewClass> {
        static constexpr ComponentDescriptor Descriptor =
            "rerun.blueprint.components.SpaceViewClass";

        /// Returns the arrow data type this type corresponds to.
        static const std::shared_ptr<arrow::DataType>& arrow_datatype() {
            return Loggable<rerun::datatypes::Utf8>::arrow_datatype();
        }

        /// Serializes an array of `rerun::blueprint:: components::SpaceViewClass` into an arrow array.
        static Result<std::shared_ptr<arrow::Array>> to_arrow(
            const blueprint::components::SpaceViewClass* instances, size_t num_instances
        ) {
            if (num_instances == 0) {
                return Loggable<rerun::datatypes::Utf8>::to_arrow(nullptr, 0);
            } else if (instances == nullptr) {
                return rerun::Error(
                    ErrorCode::UnexpectedNullArgument,
                    "Passed array instances is null when num_elements> 0."
                );
            } else {
                return Loggable<rerun::datatypes::Utf8>::to_arrow(&instances->value, num_instances);
            }
        }
    };
} // namespace rerun
