
#pragma once

#include <O3deUtils/Misc/NetworkEntityHandleWithId.h>

#include <Multiplayer/NetworkEntity/NetworkEntityHandle.h>
#include <AzCore/Component/EntityId.h>
#include <O3deUtils/Misc/MultiplayerUtils.h>
#include <Multiplayer/NetworkEntity/INetworkEntityManager.h>
#include <O3deUtils/Core/AzCoreUtils.h>
#include <CppUtils/StdReimpl/Utility.h>

namespace O3deUtils
{
    namespace Detail
    {
        template <StdReimpl::derived_from<Multiplayer::ConstNetworkEntityHandle> TNetworkEntityHandle>
        void NetworkEntityHandleWithId<TNetworkEntityHandle>::Set(const TNetworkEntityHandle& networkEntityHandle)
        {
            Set(
                networkEntityHandle,
                O3deUtils::TryGetEntityIdByNetEntityId(networkEntityHandle.GetNetEntityId())
            );
        }

        template <StdReimpl::derived_from<Multiplayer::ConstNetworkEntityHandle> TNetworkEntityHandle>
        void NetworkEntityHandleWithId<TNetworkEntityHandle>::Set(const TNetworkEntityHandle& networkEntityHandle, AZ::EntityId entityId)
        {
#if 1 // TODO: Conditionally compile based on whether assertions are enabled.
            {
                {
                    AZ::EntityId networkEntityHandleEntityId = O3deUtils::TryGetEntityIdByNetEntityId(networkEntityHandle.GetNetEntityId());
                    if (networkEntityHandleEntityId.IsValid())
                    {
                        AZStd::fixed_string<512> errorString;

                        errorString += "The two parameters should be referencing the same entity!";
                        errorString += ' ';
                        errorString += "Network entity handle's entity id: ";
                        errorString += O3deUtils::EntityIdToString(networkEntityHandleEntityId);
                        errorString += ". ";
                        errorString += "The manually passed in entity id: ";
                        errorString += O3deUtils::EntityIdToString(entityId);
                        errorString += '.';

                        AZ_Assert(entityId == networkEntityHandleEntityId, errorString.c_str());
                    }
                }

                {
                    Multiplayer::NetEntityId entityIdNetEntityId = O3deUtils::GetNetworkEntityManagerAsserted().GetNetEntityIdById(entityId);
                    if (entityIdNetEntityId != Multiplayer::InvalidNetEntityId)
                    {
                        AZStd::fixed_string<512> errorString;

                        errorString += "The two parameters should be referencing the same entity!";
                        errorString += ' ';
                        errorString += "Entity id's corresponding net entity id: ";
                        errorString += O3deUtils::IntegerToString(StdReimpl::to_underlying(entityIdNetEntityId));
                        errorString += ". ";
                        errorString += "The manually passed in network entity handle's net entity id: ";
                        errorString += O3deUtils::IntegerToString(StdReimpl::to_underlying(networkEntityHandle.GetNetEntityId()));
                        errorString += '.';

                        AZ_Assert(networkEntityHandle.GetNetEntityId() == entityIdNetEntityId, errorString.c_str());
                    }
                }
            }
#endif // #if 1

            m_networkEntityHandle = networkEntityHandle;
            m_entityId = entityId;
        }

        template <StdReimpl::derived_from<Multiplayer::ConstNetworkEntityHandle> TNetworkEntityHandle>
        void NetworkEntityHandleWithId<TNetworkEntityHandle>::Reset()
        {
            m_networkEntityHandle.Reset();
            m_entityId.SetInvalid();
        }
    }
} // namespace O3deUtils
