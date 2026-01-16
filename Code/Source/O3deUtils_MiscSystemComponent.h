
#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <O3deUtils_Misc/O3deUtils_MiscBus.h>
#include <O3deUtils_Misc/O3deUtils_MiscConfiguration.h>

namespace O3deUtils_Misc
{
    class O3DEUTILS_MISC_API O3deUtils_MiscSystemComponent
        : public AZ::Component
        , protected O3deUtils_MiscRequestBus::Handler
        , public AZ::TickBus::Handler
    {
    public:
        //
        // @Christian: Note: [engine] This uses the `AZ_COMPONENT_DECL_API` macro from custom engine fork: https://github.com/ChristianHinkle/o3de/tree/support-for-az-components-in-shared-libraries.
        //
        // I'm opening a pull request, and hopefully it eventually gets merged into the actual engine.
        //
        AZ_COMPONENT_DECL_API(O3DEUTILS_MISC_API, O3deUtils_MiscSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        O3deUtils_MiscSystemComponent();
        ~O3deUtils_MiscSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // O3deUtils_MiscRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZTickBus interface implementation
        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;
        ////////////////////////////////////////////////////////////////////////
    };

} // namespace O3deUtils_Misc
