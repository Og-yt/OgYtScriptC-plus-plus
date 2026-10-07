#ifndef PRINTLASTERRORDETAIL_HPP
#define PRINTLASTERRORDETAIL_HPP

#define WIN32_LEAN_AND_MEAN
#define FORMAT_MESSAGE FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS

#include <windows.h>
#include <ntsecapi.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

void handle_security_print_last_error_detail(LINE line_num,
                                             MESSAGE result_text,
                                             BUFFER buffer,
                                             const char* functionName,
                                             DWORD err_code)
{
    LPSTR messageBuffer = nullptr;
    DWORD size = FormatMessageA(FORMAT_MESSAGE,
                                NULL,
                                err_code,
                                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                (LPSTR)&messageBuffer,
                                0,
                                NULL);

    SecurityError::Audit::handle_print_last_error_details_error_1(line_num, result_text, buffer, functionName, err_code);

    if (size > 0 && messageBuffer != nullptr)
    {
        SecurityError::Audit::handle_security_description_print_last_err(line_num, result_text, buffer, messageBuffer);
        LocalFree(messageBuffer);
    }
    else
    {
        SecurityError::Audit::handle_unknown_error_condition(line_num, result_text, buffer);
    }
}

#endif // PRINTLASTERRORDETAIL_HPP