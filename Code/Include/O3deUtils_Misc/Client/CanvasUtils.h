
#pragma once

#if !AZ_TRAIT_CLIENT
#error "This file assumes it's being used for client code."
#endif // #if !AZ_TRAIT_CLIENT

#include <O3deUtils_Misc/O3deUtils_MiscConfiguration.h>

namespace AZ
{
    class EntityId;
}

namespace O3deUtils::Misc::CanvasUtils
{
    //! @brief Unload a canvas from the `UiCanvasManager`, but only if it's still active, because
    //!        the `UiCanvasManager` asserts if it's not active.
    O3DEUTILS_MISC_API void UnloadCanvasIfStillActive(const AZ::EntityId& canvasEntityId);
} // namespace O3deUtils::Misc::CanvasUtils
