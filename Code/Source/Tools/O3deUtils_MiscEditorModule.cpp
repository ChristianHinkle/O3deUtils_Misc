
#include <Source/O3deUtils_MiscModuleInterface.h>
#include <O3deUtils_MiscTypeIds.h>
#include <Source/Tools/O3deUtils_MiscEditorSystemComponent.h>

namespace O3deUtils
{
    class O3deUtils_MiscEditorModule : public O3deUtils_MiscModuleInterface
    {
    public:
        AZ_RTTI(O3deUtils_MiscEditorModule, O3deUtils_MiscEditorModuleTypeId, O3deUtils_MiscModuleInterface);
        AZ_CLASS_ALLOCATOR(O3deUtils_MiscEditorModule, AZ::SystemAllocator);

        O3deUtils_MiscEditorModule()
        {
            // Append editor-only items.
            m_descriptors.insert(m_descriptors.end(), {
                O3deUtils_MiscEditorSystemComponent::CreateDescriptor(),
                }
            );
        }

        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            AZ::ComponentTypeList list = O3deUtils_MiscModuleInterface::GetRequiredSystemComponents();

            // Append editor-only items.
            list.insert(list.end(), {
                azrtti_typeid<O3deUtils_MiscEditorSystemComponent>(),
                }
            );

            return list;
        }
    };
}

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME, _Editor), O3deUtils::O3deUtils_MiscEditorModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_O3deUtils_Misc_Editor, O3deUtils::O3deUtils_MiscEditorModule)
#endif
