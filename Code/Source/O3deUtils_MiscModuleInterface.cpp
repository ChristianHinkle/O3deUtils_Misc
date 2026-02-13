
#include <Source/O3deUtils_MiscModuleInterface.h>
#include <AzCore/Memory/Memory.h>

#include <O3deUtils/Misc/O3deUtils_MiscTypeIds.h>

#include <Source/O3deUtils_MiscSystemComponent.h>

namespace O3deUtils_Misc
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(O3deUtils_MiscModuleInterface,
        "O3deUtils_MiscModuleInterface", O3deUtils_MiscModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(O3deUtils_MiscModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(O3deUtils_MiscModuleInterface, AZ::SystemAllocator);

    O3deUtils_MiscModuleInterface::O3deUtils_MiscModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            O3deUtils_MiscSystemComponent::CreateDescriptor(),
            });
    }

    AZ::ComponentTypeList O3deUtils_MiscModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<O3deUtils_MiscSystemComponent>(),
        };
    }
} // namespace O3deUtils_Misc
