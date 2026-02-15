
#include <O3deUtils/Misc/MultiplayerUtils.h>

#include <AzCore/Debug/Trace.h>
#include <AzCore/Console/ILogger.h>
#include <Multiplayer/IMultiplayer.h>
#include <Multiplayer/Components/NetBindComponent.h>
#include <AzCore/Asset/AssetCommon.h>
#include <AzFramework/Spawnable/Spawnable.h>
#include <Multiplayer/MultiplayerTypes.h>
#include <Multiplayer/NetworkEntity/NetworkEntityHandle.h>

namespace O3deUtils
{
    Multiplayer::IMultiplayer& GetMultiplayerAsserted()
    {
        Multiplayer::IMultiplayer* multiplayerInterface = Multiplayer::GetMultiplayer();
        AZ_Assert(multiplayerInterface, "IMultiplayer is required.");
        return *multiplayerInterface;
    }

    Multiplayer::INetworkEntityManager& GetNetworkEntityManagerAsserted(Multiplayer::IMultiplayer& multiplayer)
    {
        Multiplayer::INetworkEntityManager* networkEntityManager = multiplayer.GetNetworkEntityManager();
        AZ_Assert(networkEntityManager, "INetworkEntityManager is required.");
        return *networkEntityManager;
    }

    bool IsHosting(Multiplayer::IMultiplayer& multiplayer)
    {
        return IsAgentTypeHosting(multiplayer.GetAgentType());
    }

    bool IsClient(Multiplayer::IMultiplayer& multiplayer)
    {
        return IsAgentTypeClient(multiplayer.GetAgentType());
    }

    void PerformHostCommand()
    {
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

        // The console command is the most generic way to start hosting level (see: `MultiplayerSystemComponent::HostConsoleCommand`). We basicaly want
        // to do whatever the "Host" console command. This way utilizes the `sv_port` and `sv_isDedicated` cvars. There is no available function declaration
        // to call on to get the same behavior so we have to perform the command like this.
        console->PerformCommand("Host");
    }

    Multiplayer::NetBindComponent& GetNetBindComponentAsserted(const AZ::Component& component)
    {
        const Multiplayer::INetworkEntityManager* networkEntityManagerPtr = Multiplayer::GetNetworkEntityManager();
        AZ_Assert(networkEntityManagerPtr, "This should always exist at this time.");
        const Multiplayer::INetworkEntityManager& networkEntityManager = *networkEntityManagerPtr;

        const Multiplayer::NetEntityId& netEntityId = networkEntityManager.GetNetEntityIdById(component.GetEntityId());
        const Multiplayer::ConstNetworkEntityHandle& netEntityHandle = networkEntityManager.GetEntity(netEntityId);

        Multiplayer::NetBindComponent* netBindComponentPtr = netEntityHandle.GetNetBindComponent();
        AZ_Assert(netBindComponentPtr, "This component is required and will always exist.");
        Multiplayer::NetBindComponent& netBindComponent = *netBindComponentPtr;

        return netBindComponent;
    }

    Multiplayer::PrefabEntityId MakeSinglePrefabEntityIdFromSpawnableAsset(const AZ::Data::Asset<AzFramework::Spawnable>& spawnableAsset)
    {
        const AZStd::size_t numEntitiesInPrefab = spawnableAsset ? spawnableAsset->GetEntities().size() : 0u;
        if (numEntitiesInPrefab > 2u)
        {
            AZStd::fixed_string<256> logString;

            logString += '`';
            logString += __func__;
            logString += "`: ";
            logString += "Prefab '";
            logString += spawnableAsset.GetHint();
            logString += "' has multiple entities. Only the first one will be used.";
            logString += ' ';
            logString += "Size of entity list: `";

            {
                AZStd::fixed_string<32> entityIdString;
                AZStd::to_string(entityIdString, numEntitiesInPrefab);

                logString += entityIdString;
            }

            logString += "`.";
            logString += ' ';
            logString += "Two is the expected value for that array.";

            AZLOG_WARN(logString.data());
        }

        // Use the first entity (ignoring the root) from the prefab.
        constexpr uint32_t prefabEntityOffset = 1u;
        return MakePrefabEntityIdFromSpawnableAsset(spawnableAsset, prefabEntityOffset);
    }

    Multiplayer::PrefabEntityId MakePrefabEntityIdFromSpawnableAsset(const AZ::Data::Asset<AzFramework::Spawnable>& spawnableAsset, uint32_t entityOffset)
    {
        return Multiplayer::PrefabEntityId{
            AZ::Name{spawnableAsset.GetHint()},
            entityOffset
        };
    }

    bool IsNetworkEntityHandleSet(const Multiplayer::ConstNetworkEntityHandle& value)
    {
        bool result = value.GetNetEntityId() != Multiplayer::InvalidNetEntityId;

        if (!result)
        {
            AZ_Assert(!value.GetEntity(), "The network entity handle is an InvalidNetEntityId, but the entity is valid. This is weird.");
            AZ_Assert(!value.GetNetBindComponent(), "The network entity handle is an InvalidNetEntityId, but the net bind component is valid. This is weird.");
        }

        return result;
    }
} // namespace O3deUtils
