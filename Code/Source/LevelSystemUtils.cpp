
#include <O3deUtils/Misc/LevelSystemUtils.h>

#include <AzCore/Console/ILogger.h>
#include <AzCore/Debug/Trace.h>
#include <platform.h>
#include <CryCommon/ISystem.h>
#include <CryCommon/ILevelSystem.h>
#include <AzCore/Console/IConsole.h>

namespace O3deUtils::LevelSystemUtils
{
    void TryLoadLevel(const AZStd::string_view& levelName)
    {
        if (levelName.empty())
        {
            AZStd::fixed_string<128> logString;

            logString += '`';
            logString += __func__;
            logString += "`: ";
            logString += "Level name to load is empty. Doing nothing and returning early.";

            AZLOG_INFO(logString.data());
            return;
        }

        LoadLevel(levelName);
    }

    void LoadLevel(const AZStd::string_view& levelName)
    {
        AZ_Assert(!levelName.empty(), "This function expects a non-empty level name to be passed in. Consider using: `TryLoadLevel` instead.");

        AZ::IConsole* console = AZ::Interface<AZ::IConsole>::Get();
        if (!console)
        {
            AZStd::fixed_string<128> logString;

            logString += '`';
            logString += __func__;
            logString += "`: ";
            logString += "IConsole is null. Doing nothing and returning early.";

            AZLOG_INFO(logString.data());
            return;
        }

        // The console command is the only generic way to load a level without digging into using the right systems. We basicaly want
        // to do whatever the `AZ_CONSOLEFREEFUNC` of "LoadLevel" does when it's called. There is no available function declaration to
        // call on to get the same behavior so we have to perform the command like this.
        AZStd::fixed_string<128> consoleCommand;
        consoleCommand += "LoadLevel";
        consoleCommand += ' ';
        consoleCommand += levelName;

        console->PerformCommand(consoleCommand.data());
    }
} // namespace O3deUtils::LevelSystemUtils
