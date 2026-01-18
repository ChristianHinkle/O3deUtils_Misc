
#include <O3deUtils_Misc/MultiplayerUtils.h>

#include <AzCore/Debug/Trace.h>
#include <AzCore/Console/ILogger.h>
#include <Multiplayer/IMultiplayer.h>
#include <Multiplayer/Components/NetBindComponent.h>

namespace O3deUtils::Misc::MultiplayerUtils
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

    bool IsHosting()
    {
        const Multiplayer::MultiplayerAgentType currentMultiplayerAgentType = GetMultiplayerAsserted().GetAgentType();

        switch (currentMultiplayerAgentType)
        {
        case Multiplayer::MultiplayerAgentType::ClientServer:
        case Multiplayer::MultiplayerAgentType::DedicatedServer:
            return true;
        }

        return false;
    }

    bool IsClient()
    {
        const Multiplayer::MultiplayerAgentType currentMultiplayerAgentType = GetMultiplayerAsserted().GetAgentType();

        switch (currentMultiplayerAgentType)
        {
        case Multiplayer::MultiplayerAgentType::Client:
            return true;
        }

        return false;
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
} // namespace O3deUtils::Misc::MultiplayerUtils
