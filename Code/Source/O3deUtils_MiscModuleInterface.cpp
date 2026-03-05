
#include <Source/O3deUtils_MiscModuleInterface.h>

#include <AzCore/Memory/Memory.h>

#include <O3deUtils_MiscTypeIds.h>

#include <Source/O3deUtils_MiscSystemComponent.h>

namespace O3deUtils
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(O3deUtils_MiscModuleInterface, "O3deUtils_MiscModuleInterface", O3deUtils_MiscModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(O3deUtils_MiscModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(O3deUtils_MiscModuleInterface, AZ::SystemAllocator);

    O3deUtils_MiscModuleInterface::O3deUtils_MiscModuleInterface()
    {
        // Append all items used by both editor and non-editor targets.
        m_descriptors.insert(m_descriptors.end(), {
            O3deUtils_MiscSystemComponent::CreateDescriptor(),
            }
        );
    }

    AZ::ComponentTypeList O3deUtils_MiscModuleInterface::GetRequiredSystemComponents() const
    {
        // Append all items used by both editor and non-editor targets.
        return AZ::ComponentTypeList{
        };
    }
}
