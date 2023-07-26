// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/archetypes/points3d.fbs"

#pragma once

#include "../components/class_id.hpp"
#include "../components/color.hpp"
#include "../components/draw_order.hpp"
#include "../components/instance_key.hpp"
#include "../components/keypoint_id.hpp"
#include "../components/label.hpp"
#include "../components/point3d.hpp"
#include "../components/radius.hpp"

#include <arrow/type_fwd.h>
#include <cstdint>
#include <optional>
#include <vector>

namespace rr {
    namespace archetypes {
        /// A 3D point cloud with positions and optional colors, radii, labels, etc.
        struct Points3D {
            /// All the actual 3D points that make up the point cloud.
            std::vector<rr::components::Point3D> points;

            /// Optional radii for the points, effectively turning them into circles.
            std::optional<std::vector<rr::components::Radius>> radii;

            /// Optional colors for the points.
            std::optional<std::vector<rr::components::Color>> colors;

            /// Optional text labels for the points.
            std::optional<std::vector<rr::components::Label>> labels;

            /// An optional floating point value that specifies the 3D drawing order.
            /// Objects with higher values are drawn on top of those with lower values.
            ///
            /// The default for 3D points is 30.0.
            std::optional<rr::components::DrawOrder> draw_order;

            /// Optional class Ids for the points.
            ///
            /// The class ID provides colors and labels if not specified explicitly.
            std::optional<std::vector<rr::components::ClassId>> class_ids;

            /// Optional keypoint IDs for the points, identifying them within a class.
            ///
            /// If keypoint IDs are passed in but no class IDs were specified, the class ID will
            /// default to 0.
            /// This is useful to identify points within a single classification (which is
            /// identified with `class_id`). E.g. the classification might be 'Person' and the
            /// keypoints refer to joints on a detected skeleton.
            std::optional<std::vector<rr::components::KeypointId>> keypoint_ids;

            /// Unique identifiers for each individual point in the batch.
            std::optional<std::vector<rr::components::InstanceKey>> instance_keys;
        };
    } // namespace archetypes
} // namespace rr
