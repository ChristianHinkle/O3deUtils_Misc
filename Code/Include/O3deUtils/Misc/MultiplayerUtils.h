
#pragma once

#include <O3deUtils/Misc/O3deUtils_MiscConfiguration.h>
#include <Multiplayer/MultiplayerTypes.h>

namespace AZ
{
    class Component;

    namespace Data
    {
        template <class T>
        class Asset;
    }
}

namespace AzFramework
{
    class Spawnable;
}

namespace Multiplayer
{
    class IMultiplayer;
    class INetworkEntityManager;
    class NetBindComponent;
    struct PrefabEntityId;
    enum class MultiplayerAgentType;
}

namespace O3deUtils::MultiplayerUtils
{
    //! @brief A version of `Multiplayer::GetMultiplayer` that returns a reference rather than a pointer.
    O3DEUTILS_MISC_API Multiplayer::IMultiplayer& GetMultiplayerAsserted();

    //! @brief A version of `Multiplayer::GetNetworkEntityManager` that returns a reference rather than a pointer. Also is
    //!        based on the multiplayer interface reference argument passed in.
    O3DEUTILS_MISC_API Multiplayer::INetworkEntityManager& GetNetworkEntityManagerAsserted(Multiplayer::IMultiplayer& multiplayer = GetMultiplayerAsserted());

    //! @brief A mirrored implementation of `MultiplayerSystemComponent::IsHosting`.
    O3DEUTILS_MISC_API bool IsHosting(Multiplayer::IMultiplayer& multiplayer = GetMultiplayerAsserted());

    O3DEUTILS_MISC_API bool IsClient(Multiplayer::IMultiplayer& multiplayer = GetMultiplayerAsserted());

    O3DEUTILS_MISC_API constexpr bool IsAgentTypeHosting(const Multiplayer::MultiplayerAgentType agentType);

    O3DEUTILS_MISC_API constexpr bool IsAgentTypeClient(const Multiplayer::MultiplayerAgentType agentType);

    //! @brief Starts hosting. Same behavior as the "Host" console command.
    O3DEUTILS_MISC_API void PerformHostCommand();

    O3DEUTILS_MISC_API Multiplayer::NetBindComponent& GetNetBindComponentAsserted(const AZ::Component& component);

    //! @brief Constructs a PrefabEntityId from a spawnable asset reference with the intention of it only producing a single entity.
    O3DEUTILS_MISC_API Multiplayer::PrefabEntityId MakeSinglePrefabEntityIdFromSpawnableAsset(
        const AZ::Data::Asset<AzFramework::Spawnable>& spawnableAsset);

    O3DEUTILS_MISC_API Multiplayer::PrefabEntityId MakePrefabEntityIdFromSpawnableAsset(
        const AZ::Data::Asset<AzFramework::Spawnable>& spawnableAsset,
        uint32_t entityOffset = Multiplayer::PrefabEntityId::AllIndices);
} // namespace O3deUtils::MultiplayerUtils

#include <O3deUtils/Misc/MultiplayerUtils.inl>
