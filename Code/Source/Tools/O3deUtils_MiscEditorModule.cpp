
#include <O3deUtils_Misc/O3deUtils_MiscTypeIds.h>
#include <O3deUtils_MiscModuleInterface.h>
#include "O3deUtils_MiscEditorSystemComponent.h"

namespace O3deUtils_Misc
{
    class O3deUtils_MiscEditorModule
        : public O3deUtils_MiscModuleInterface
    {
    public:
        AZ_RTTI(O3deUtils_MiscEditorModule, O3deUtils_MiscEditorModuleTypeId, O3deUtils_MiscModuleInterface);
        AZ_CLASS_ALLOCATOR(O3deUtils_MiscEditorModule, AZ::SystemAllocator);

        O3deUtils_MiscEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                O3deUtils_MiscEditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<O3deUtils_MiscEditorSystemComponent>(),
            };
        }
    };
}// namespace O3deUtils_Misc

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME, _Editor), O3deUtils_Misc::O3deUtils_MiscEditorModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_O3deUtils_Misc_Editor, O3deUtils_Misc::O3deUtils_MiscEditorModule)
#endif
