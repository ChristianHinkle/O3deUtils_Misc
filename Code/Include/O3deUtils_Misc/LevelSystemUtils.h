
#pragma once

#include <AzCore/std/string/string_view.h>

namespace O3deUtils::Misc::LevelSystemUtils
{
    void TryLoadLevel(const AZStd::string_view& levelName);

    void LoadLevel(const AZStd::string_view& levelName);
} // namespace O3deUtils::Misc::LevelSystemUtils
