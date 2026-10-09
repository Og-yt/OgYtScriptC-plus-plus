#ifndef METHOD3CONSTRUCTATARGETSACLUSINGSDDLSTRING_HPP
#define METHOD3CONSTRUCTATARGETSACLUSINGSDDLSTRING_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include <sstream>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_step_3_construct_a_target_sacl_using_sddl_string(std::wostringstream &oss,
                                                                    PSECURITY_DESCRIPTOR pNewSD,
                                                                    PSECURITY_DESCRIPTOR pOriginalSD,
                                                                    LINE line_num,
                                                                    MESSAGE result_text,
                                                                    BUFFER buffer)
{
    LPCSTR szTargetSddl = "S:(AU;SA FA;0x120116;;;WD)";
    oss << "[4] Building new Global SACL from SDDL string:\n";
    oss << "    SDDL: " << szTargetSddl << "\n";

    ULONG ulSdSize = 0;

    if (!ConvertStringSecurityDescriptorToSecurityDescriptorA(szTargetSddl,
                                                              SDDL_REVISION_1,
                                                              &pNewSD,
                                                              &ulSdSize))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_failed_to_parse_sddl_error(line_num, result_text, buffer, err_code);

        if (pOriginalSD != NULL)
        {
            LsaFreeMemory(pOriginalSD);
        }
        return 1;
    }
}

#endif // METHOD3CONSTRUCTATARGETSACLUSINGSDDLSTRING_HPP