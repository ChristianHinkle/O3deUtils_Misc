
#include <AzCore/Memory/Memory_fwd.h>
#include <AzCore/Module/Module.h>
#include <AzCore/RTTI/RTTIMacros.h>
#include <AzCore/RTTI/TypeInfoSimple.h>
#include <O3deUtils/Misc/O3deUtils_MiscConfiguration.h>

namespace O3deUtils_Misc
{
    class O3DEUTILS_MISC_API O3deUtils_MiscModuleInterface
        : public AZ::Module
    {
    public:
        AZ_TYPE_INFO_WITH_NAME_DECL_API(O3DEUTILS_MISC_API, O3deUtils_MiscModuleInterface)
        AZ_RTTI_NO_TYPE_INFO_DECL()
        AZ_CLASS_ALLOCATOR_DECL

        O3deUtils_MiscModuleInterface();

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override;
    };
}// namespace O3deUtils_Misc
