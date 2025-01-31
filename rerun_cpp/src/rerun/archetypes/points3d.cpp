// DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/store/re_types/definitions/rerun/archetypes/points3d.fbs".

#include "points3d.hpp"

#include "../collection_adapter_builtins.hpp"

namespace rerun::archetypes {}

namespace rerun {

    Result<std::vector<ComponentBatch>> AsComponents<archetypes::Points3D>::serialize(
        const archetypes::Points3D& archetype
    ) {
        using namespace archetypes;
        std::vector<ComponentBatch> cells;
        cells.reserve(8);

        {
            auto result = ComponentBatch::from_loggable(
                archetype.positions,
                ComponentDescriptor(
                    "rerun.archetypes.Points3D",
                    "positions",
                    "rerun.components.Position3D"
                )
            );
            RR_RETURN_NOT_OK(result.error);
            cells.push_back(std::move(result.value));
        }
        if (archetype.radii.has_value()) {
            auto result = ComponentBatch::from_loggable(
                archetype.radii.value(),
                ComponentDescriptor("rerun.archetypes.Points3D", "radii", "rerun.components.Radius")
            );
            RR_RETURN_NOT_OK(result.error);
            cells.push_back(std::move(result.value));
        }
        if (archetype.colors.has_value()) {
            auto result = ComponentBatch::from_loggable(
                archetype.colors.value(),
                ComponentDescriptor("rerun.archetypes.Points3D", "colors", "rerun.components.Color")
            );
            RR_RETURN_NOT_OK(result.error);
            cells.push_back(std::move(result.value));
        }
        if (archetype.labels.has_value()) {
            auto result = ComponentBatch::from_loggable(
                archetype.labels.value(),
                ComponentDescriptor("rerun.archetypes.Points3D", "labels", "rerun.components.Text")
            );
            RR_RETURN_NOT_OK(result.error);
            cells.push_back(std::move(result.value));
        }
        if (archetype.show_labels.has_value()) {
            auto result = ComponentBatch::from_loggable(
                archetype.show_labels.value(),
                ComponentDescriptor(
                    "rerun.archetypes.Points3D",
                    "show_labels",
                    "rerun.components.ShowLabels"
                )
            );
            RR_RETURN_NOT_OK(result.error);
            cells.push_back(std::move(result.value));
        }
        if (archetype.class_ids.has_value()) {
            auto result = ComponentBatch::from_loggable(
                archetype.class_ids.value(),
                ComponentDescriptor(
                    "rerun.archetypes.Points3D",
                    "class_ids",
                    "rerun.components.ClassId"
                )
            );
            RR_RETURN_NOT_OK(result.error);
            cells.push_back(std::move(result.value));
        }
        if (archetype.keypoint_ids.has_value()) {
            auto result = ComponentBatch::from_loggable(
                archetype.keypoint_ids.value(),
                ComponentDescriptor(
                    "rerun.archetypes.Points3D",
                    "keypoint_ids",
                    "rerun.components.KeypointId"
                )
            );
            RR_RETURN_NOT_OK(result.error);
            cells.push_back(std::move(result.value));
        }
        {
            auto indicator = Points3D::IndicatorComponent();
            auto result = ComponentBatch::from_loggable(indicator);
            RR_RETURN_NOT_OK(result.error);
            cells.emplace_back(std::move(result.value));
        }

        return cells;
    }
} // namespace rerun
