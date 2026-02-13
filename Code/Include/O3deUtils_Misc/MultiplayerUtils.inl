
#pragma once

#include <O3deUtils_Misc/MultiplayerUtils.h>

#include <Multiplayer/IMultiplayer.h>

constexpr bool O3deUtils::Misc::MultiplayerUtils::IsAgentTypeHosting(const Multiplayer::MultiplayerAgentType agentType)
{
    switch (agentType)
    {
    case Multiplayer::MultiplayerAgentType::ClientServer:
    case Multiplayer::MultiplayerAgentType::DedicatedServer:
        return true;
    }

    return false;
}

constexpr bool O3deUtils::Misc::MultiplayerUtils::IsAgentTypeClient(const Multiplayer::MultiplayerAgentType agentType)
{
    // @Christian: TODO: [todo][multiplayer] Make the name of this function more clear or have it also return true for `ClientServer`. We should probably have a third function to provide all the combination of queries people might want to use. Right now, the same of this function could be misleading though.
    switch (agentType)
    {
    case Multiplayer::MultiplayerAgentType::Client:
        return true;
    }

    return false;
}
