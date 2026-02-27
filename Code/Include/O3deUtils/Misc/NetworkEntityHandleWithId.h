
#pragma once

#include <O3deUtils/Misc/O3deUtils_MiscConfiguration.h>
#include <CppUtils/StdReimpl/concepts.h>
#include <Multiplayer/NetworkEntity/NetworkEntityHandle.h>

namespace AZ
{
    class EntityId;
}

namespace Multiplayer
{
    class ConstNetworkEntityHandle;
    class NetworkEntityHandle;
}

namespace O3deUtils
{
    namespace Detail
    {
        //! @brief Holds external references to a network entity handle and an entity id and ensures they are
        //!        refering to the same entity when modifying their values.
        template <StdReimpl::derived_from<Multiplayer::ConstNetworkEntityHandle> TNetworkEntityHandle>
        struct NetworkEntityHandleWithId
        {
        public:

            explicit NetworkEntityHandleWithId(TNetworkEntityHandle& networkEntityHandle, AZ::EntityId& entityId)
                : m_networkEntityHandle{networkEntityHandle}
                , m_entityId{entityId}
            {
            }

            NetworkEntityHandleWithId(const NetworkEntityHandleWithId&) = default;
            NetworkEntityHandleWithId& operator=(const NetworkEntityHandleWithId&) = default;

        public:

            const Multiplayer::ConstNetworkEntityHandle& GetNetworkEntityHandle() const { return m_networkEntityHandle; }
            AZ::EntityId GetEntityId() const { return m_entityId; }

            void Set(const TNetworkEntityHandle& networkEntityHandle);
            void Set(const TNetworkEntityHandle& networkEntityHandle, AZ::EntityId entityId);

            void Reset();

        private:

            TNetworkEntityHandle& m_networkEntityHandle;
            AZ::EntityId& m_entityId;
        };

        // Explicitly instantiate and export/import the possible templates specializations.
        template struct O3DEUTILS_MISC_API NetworkEntityHandleWithId<Multiplayer::ConstNetworkEntityHandle>;
        template struct O3DEUTILS_MISC_API NetworkEntityHandleWithId<Multiplayer::NetworkEntityHandle>;
    }

    // Provide nice type aliases to the template class.
    using NetworkEntityHandleWithId = Detail::NetworkEntityHandleWithId<Multiplayer::NetworkEntityHandle>;
    using ConstNetworkEntityHandleWithId = Detail::NetworkEntityHandleWithId<Multiplayer::ConstNetworkEntityHandle>;
} // namespace O3deUtils

#include <O3deUtils/Misc/NetworkEntityHandleWithId.inl>
