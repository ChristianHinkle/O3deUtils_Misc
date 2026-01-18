
#pragma once

#include <O3deUtils_Misc/O3deUtils_MiscConfiguration.h>

namespace AZ
{
    class Component;
}

namespace Multiplayer
{
    class IMultiplayer;
    class INetworkEntityManager;
    class NetBindComponent;
}

namespace O3deUtils::Misc::MultiplayerUtils
{
    //! @brief A version of `Multiplayer::GetMultiplayer` that returns a reference rather than a pointer.
    O3DEUTILS_MISC_API Multiplayer::IMultiplayer& GetMultiplayerAsserted();

    //! @brief A version of `Multiplayer::GetNetworkEntityManager` that returns a reference rather than a pointer. Also is
    //!        based on the multiplayer interface reference argument passed in.
    O3DEUTILS_MISC_API Multiplayer::INetworkEntityManager& GetNetworkEntityManagerAsserted(Multiplayer::IMultiplayer& multiplayer = GetMultiplayerAsserted());

    //! @brief A mirrored implementation of `MultiplayerSystemComponent::IsHosting`.
    O3DEUTILS_MISC_API bool IsHosting();

    O3DEUTILS_MISC_API bool IsClient();

    //! @brief Starts hosting. Same behavior as the "Host" console command.
    O3DEUTILS_MISC_API void PerformHostCommand();

    O3DEUTILS_MISC_API Multiplayer::NetBindComponent& GetNetBindComponentAsserted(const AZ::Component& component);
} // namespace O3deUtils::Misc::MultiplayerUtils
