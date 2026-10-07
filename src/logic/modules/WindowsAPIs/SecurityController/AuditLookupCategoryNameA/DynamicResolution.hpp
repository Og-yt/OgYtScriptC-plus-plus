#ifndef DYNAMICRESOLUTION_HPP
#define DYNAMICRESOLUTION_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <ostream>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../PrintLastErrorDetail/PrintLastErrorDetail.hpp"
#include "../AuditLookupCategoryNameA/AuditLookupCategoryNameAStructure.hpp"

inline bool handle_method_2_dynamic_resolution(LINE line_num,
                                               MESSAGE result_text,
                                               BUFFER buffer)
{
    std::stringstream oss;
    DWORD err_code = GetLastError();

    oss << "--- Dynamic Module Loading (Explicit DLL Import) ---\n";

    HMODULE hAdvApi32 = LoadLibraryA("advapi32.dll");
    if (hAdvApi32 == NULL)
    {
        handle_security_print_last_error_detail(line_num, result_text, buffer, "LoadLibraryA(\"advapi32.dll\")", std::to_string(err_code));
        return 1;
    }

    PFN_AuditLookupCategoryNameA pfnAuditLookupCategoryNameA = (PFN_AuditLookupCategoryNameA)GetProcAddress(hAdvApi32, "AuditLookupCategoryNameA");
    PFN_AuditFree pfnAuditFree = (PFN_AuditFree)GetProcAddress(hAdvApi32, "AuditFree");

    if (pfnAuditLookupCategoryNameA == NULL || pfnAuditFree == NULL)
    {
        //
        FreeLibrary(hAdvApi32);
        return 1;
    }

    oss << "Successfully resolved function pointers from advapi32.dll.\n";

    GUID targetGuid = AuditCategorySystem;
}

#endif // DYNAMICRESOLUTION_HPP