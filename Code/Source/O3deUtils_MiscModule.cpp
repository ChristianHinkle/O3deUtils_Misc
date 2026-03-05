
#include <Source/O3deUtils_MiscModuleInterface.h>
#include <O3deUtils_MiscTypeIds.h>
#include <Source/O3deUtils_MiscSystemComponent.h>

namespace O3deUtils
{
    class O3deUtils_MiscModule : public O3deUtils_MiscModuleInterface
    {
    public:
        AZ_RTTI(O3deUtils_MiscModule, O3deUtils_MiscModuleTypeId, O3deUtils_MiscModuleInterface);
        AZ_CLASS_ALLOCATOR(O3deUtils_MiscModule, AZ::SystemAllocator);

        O3deUtils_MiscModule()
        {
            // Append non-editor items.
            m_descriptors.insert(m_descriptors.end(), {
                }
            );
        }

        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            AZ::ComponentTypeList list = O3deUtils_MiscModuleInterface::GetRequiredSystemComponents();

            // Append non-editor items.
            list.insert(list.end(), {
                azrtti_typeid<O3deUtils_MiscSystemComponent>(),
                }
            );

            return list;
        }
    };
}

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), O3deUtils::O3deUtils_MiscModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_O3deUtils_Misc, O3deUtils::O3deUtils_MiscModule)
#endif
