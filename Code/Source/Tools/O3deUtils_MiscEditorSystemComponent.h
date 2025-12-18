
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Source/O3deUtils_MiscSystemComponent.h>

namespace O3deUtils_Misc
{
    /// System component for O3deUtils_Misc editor
    class O3deUtils_MiscEditorSystemComponent
        : public O3deUtils_MiscSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = O3deUtils_MiscSystemComponent;
    public:
        AZ_COMPONENT_DECL(O3deUtils_MiscEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        O3deUtils_MiscEditorSystemComponent();
        ~O3deUtils_MiscEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace O3deUtils_Misc
