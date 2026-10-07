#ifndef DYNAMICRESOLUTION_HPP
#define DYNAMICRESOLUTION_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../PrintLastErrorDetail/PrintLastErrorDetail.hpp"
#include "../AuditLookupCategoryNameA/AuditLookupCategoryNameAStructure.hpp"

inline bool handle_method_2_dynamic_resolution(LINE line_num,
                                               MESSAGE result_text,
                                               BUFFER buffer)
{
    std::stringstream oss;


    oss << "--- Dynamic Module Loading (Explicit DLL Import) ---\n";

    HMODULE hAdvApi32 = LoadLibraryA("advapi32.dll");
    if (hAdvApi32 == NULL)
    {
        DWORD err_code = GetLastError();
        handle_security_print_last_error_detail(line_num, result_text, buffer, "LoadLibraryA(\"advapi32.dll\")", err_code);
        return false;
    }

    PFN_AuditLookupCategoryNameA pfnAuditLookupCategoryNameA = (PFN_AuditLookupCategoryNameA)GetProcAddress(hAdvApi32, "AuditLookupCategoryNameA");
    PFN_AuditFree pfnAuditFree = (PFN_AuditFree)GetProcAddress(hAdvApi32, "AuditFree");

    if (pfnAuditLookupCategoryNameA == NULL || pfnAuditFree == NULL)
    {
        SecurityError::Audit::handle_failed_to_resolve_function_error(line_num, result_text, buffer);
        FreeLibrary(hAdvApi32);
        return false;
    }

    oss << "Successfully resolved function pointers from advapi32.dll.\n";

    GUID targetGuid = {};
    if (!AuditLookupCategoryGuidFromCategoryId(AuditCategorySystem, &targetGuid))
    {
        DWORD err_code = GetLastError();
        handle_security_print_last_error_detail(
            line_num, result_text, buffer,
            "AuditLookupCategoryGuidFromCategoryId", err_code);
        FreeLibrary(hAdvApi32);
        return false;
    }

    PSTR pDynamicCategoryName = nullptr;

    BOOL dynamicResult = pfnAuditLookupCategoryNameA(&targetGuid, &pDynamicCategoryName);
    if (dynamicResult && pDynamicCategoryName != nullptr)
    {
        oss << "  Dynamic Lookup Output: \"" << pDynamicCategoryName << "\"\n";
        pfnAuditFree(pDynamicCategoryName);
        pDynamicCategoryName = nullptr;
    }
    else
    {
        DWORD err_code = GetLastError();
        handle_security_print_last_error_detail(line_num, result_text, buffer, "pfnAuditLookupCategoryNameA", err_code);
    }

    FreeLibrary(hAdvApi32);
    result_text += oss.str();
    return dynamicResult != FALSE;
}

#endif // DYNAMICRESOLUTION_HPP