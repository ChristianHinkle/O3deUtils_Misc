
#pragma once

#include <O3deUtils/Misc/O3deUtils_MiscTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace O3deUtils_Misc
{
    class O3deUtils_MiscRequests
    {
    public:
        AZ_RTTI(O3deUtils_MiscRequests, O3deUtils_MiscRequestsTypeId);
        virtual ~O3deUtils_MiscRequests() = default;
        // Put your public methods here
    };

    class O3deUtils_MiscBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using O3deUtils_MiscRequestBus = AZ::EBus<O3deUtils_MiscRequests, O3deUtils_MiscBusTraits>;
    using O3deUtils_MiscInterface = AZ::Interface<O3deUtils_MiscRequests>;

} // namespace O3deUtils_Misc
