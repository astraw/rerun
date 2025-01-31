# DO NOT EDIT! This file was auto-generated by crates/build/re_types_builder/src/codegen/python/mod.rs
# Based on "crates/store/re_types/definitions/rerun/blueprint/components/auto_space_views.fbs".

# You can extend this class by creating a "AutoSpaceViewsExt" class in "auto_space_views_ext.py".

from __future__ import annotations

from ... import datatypes
from ..._baseclasses import (
    ComponentBatchMixin,
    ComponentDescriptor,
    ComponentMixin,
)

__all__ = ["AutoSpaceViews", "AutoSpaceViewsBatch"]


class AutoSpaceViews(datatypes.Bool, ComponentMixin):
    """**Component**: Whether or not space views should be created automatically."""

    _BATCH_TYPE = None
    # You can define your own __init__ function as a member of AutoSpaceViewsExt in auto_space_views_ext.py

    # Note: there are no fields here because AutoSpaceViews delegates to datatypes.Bool
    pass


class AutoSpaceViewsBatch(datatypes.BoolBatch, ComponentBatchMixin):
    _COMPONENT_DESCRIPTOR: ComponentDescriptor = ComponentDescriptor("rerun.blueprint.components.AutoSpaceViews")


# This is patched in late to avoid circular dependencies.
AutoSpaceViews._BATCH_TYPE = AutoSpaceViewsBatch  # type: ignore[assignment]
