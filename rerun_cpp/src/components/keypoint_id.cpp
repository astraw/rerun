// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/components/keypoint_id.fbs"

#include "keypoint_id.hpp"

#include <arrow/api.h>

namespace rr {
    namespace components {
        std::shared_ptr<arrow::DataType> KeypointId::to_arrow_datatype() {
            return arrow::uint16();
        }

        arrow::Result<std::shared_ptr<arrow::UInt16Builder>> KeypointId::new_arrow_array_builder(
            arrow::MemoryPool* memory_pool
        ) {
            if (!memory_pool) {
                return arrow::Status::Invalid("Memory pool is null.");
            }

            return arrow::Result(std::make_shared<arrow::UInt16Builder>(memory_pool));
        }

        arrow::Status KeypointId::fill_arrow_array_builder(
            arrow::UInt16Builder* builder, const KeypointId* elements, size_t num_elements
        ) {
            if (!builder) {
                return arrow::Status::Invalid("Passed array builder is null.");
            }
            if (!elements) {
                return arrow::Status::Invalid("Cannot serialize null pointer to arrow array.");
            }

            static_assert(sizeof(*elements) == sizeof(elements->id));
            ARROW_RETURN_NOT_OK(builder->AppendValues(&elements->id, num_elements));

            return arrow::Status::OK();
        }
    } // namespace components
} // namespace rr
