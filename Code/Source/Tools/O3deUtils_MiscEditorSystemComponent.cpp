
#include <AzCore/Serialization/SerializeContext.h>
#include "O3deUtils_MiscEditorSystemComponent.h"

#include <O3deUtils_Misc/O3deUtils_MiscTypeIds.h>

namespace O3deUtils_Misc
{
    AZ_COMPONENT_IMPL(O3deUtils_MiscEditorSystemComponent, "O3deUtils_MiscEditorSystemComponent",
        O3deUtils_MiscEditorSystemComponentTypeId, BaseSystemComponent);

    void O3deUtils_MiscEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<O3deUtils_MiscEditorSystemComponent, O3deUtils_MiscSystemComponent>()
                ->Version(0);
        }
    }

    O3deUtils_MiscEditorSystemComponent::O3deUtils_MiscEditorSystemComponent() = default;

    O3deUtils_MiscEditorSystemComponent::~O3deUtils_MiscEditorSystemComponent() = default;

    void O3deUtils_MiscEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("O3deUtils_MiscEditorService"));
    }

    void O3deUtils_MiscEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("O3deUtils_MiscEditorService"));
    }

    void O3deUtils_MiscEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void O3deUtils_MiscEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void O3deUtils_MiscEditorSystemComponent::Activate()
    {
        O3deUtils_MiscSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void O3deUtils_MiscEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        O3deUtils_MiscSystemComponent::Deactivate();
    }

} // namespace O3deUtils_Misc
