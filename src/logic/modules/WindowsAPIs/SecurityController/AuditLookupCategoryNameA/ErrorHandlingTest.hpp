#ifndef ERRORHANDLINGTEST_HPP
#define ERRORHANDLINGTEST_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <ostream>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../PrintLastErrorDetail/PrintLastErrorDetail.hpp"

inline bool handle_method_3_error_handling_test(LINE line_num,
                                                MESSAGE result_text,
                                                BUFFER buffer)
{
    std::ostringstream oss;

    oss << "\n--- Invalid GUID Test ---\n";
    GUID invalidGuid = {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
    PSTR pFailBuffer = nullptr;

    BOOL failResult = AuditLookupCategoryNameA(&invalidGuid, &pFailBuffer);
    if (!failResult)
    {
        DWORD exceptedError = GetLastError();
        handle_security_print_last_error_detail(line_num, result_text, buffer, "AuditLookupCategoryNameA (Invalid GUID)", exceptedError);
    }
    else
    {
        if (pFailBuffer)
        {
            AuditFree(pFailBuffer);
        }
    }

    result_text += oss.str();
    return false;
}

#endif // ERRORHANDLINGTEST_HPP