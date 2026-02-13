
#pragma once

namespace O3deUtils_Misc
{
    // System Component TypeIds
    inline constexpr const char* O3deUtils_MiscSystemComponentTypeId = "{F2EB846E-5FFC-4275-B66C-EB70DC2A7FE7}";
    inline constexpr const char* O3deUtils_MiscEditorSystemComponentTypeId = "{434E7C84-D770-4641-85BE-D1A2E98B4648}";

    // Module derived classes TypeIds
    inline constexpr const char* O3deUtils_MiscModuleInterfaceTypeId = "{8B8E4566-F3B0-4165-ADAE-6FFA9BD0F8E9}";
    inline constexpr const char* O3deUtils_MiscModuleTypeId = "{E76A6970-3368-4A13-A0A5-A74C68068FB2}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* O3deUtils_MiscEditorModuleTypeId = O3deUtils_MiscModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* O3deUtils_MiscRequestsTypeId = "{C6D634C3-B071-4A02-A40E-B93248634B62}";
} // namespace O3deUtils_Misc
