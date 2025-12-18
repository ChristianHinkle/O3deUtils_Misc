
#include <Source/O3deUtils_MiscSystemComponent.h>

#include <O3deUtils_Misc/O3deUtils_MiscTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>

namespace O3deUtils_Misc
{
    AZ_COMPONENT_IMPL(O3deUtils_MiscSystemComponent, "O3deUtils_MiscSystemComponent",
        O3deUtils_MiscSystemComponentTypeId);

    void O3deUtils_MiscSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<O3deUtils_MiscSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void O3deUtils_MiscSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("O3deUtils_MiscService"));
    }

    void O3deUtils_MiscSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("O3deUtils_MiscService"));
    }

    void O3deUtils_MiscSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void O3deUtils_MiscSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    O3deUtils_MiscSystemComponent::O3deUtils_MiscSystemComponent()
    {
        if (O3deUtils_MiscInterface::Get() == nullptr)
        {
            O3deUtils_MiscInterface::Register(this);
        }
    }

    O3deUtils_MiscSystemComponent::~O3deUtils_MiscSystemComponent()
    {
        if (O3deUtils_MiscInterface::Get() == this)
        {
            O3deUtils_MiscInterface::Unregister(this);
        }
    }

    void O3deUtils_MiscSystemComponent::Init()
    {
    }

    void O3deUtils_MiscSystemComponent::Activate()
    {
        O3deUtils_MiscRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void O3deUtils_MiscSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        O3deUtils_MiscRequestBus::Handler::BusDisconnect();
    }

    void O3deUtils_MiscSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace O3deUtils_Misc
