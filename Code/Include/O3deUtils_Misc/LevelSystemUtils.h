
#pragma once

#include <AzCore/std/string/string_view.h>
#include <O3deUtils_Misc/O3deUtils_MiscConfiguration.h>

namespace O3deUtils::Misc::LevelSystemUtils
{
    O3DEUTILS_MISC_API void TryLoadLevel(const AZStd::string_view& levelName);

    O3DEUTILS_MISC_API void LoadLevel(const AZStd::string_view& levelName);
} // namespace O3deUtils::Misc::LevelSystemUtils
