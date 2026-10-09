#ifndef METHOD2TARGETOBJECTSUBSYSTEM_HPP
#define METHOD2TARGETOBJECTSUBSYSTEM_HPP

#include <windows.h>
#include <ntsecapi.h>

#include <sstream>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_step_2_target_object_sub_system(std::wostringstream &oss,
                                                   PCSTR szObjectTypeName,
                                                   PACL ppOriginalSD,
                                                   PSECURITY_DESCRIPTOR pOriginalSD,
                                                   LINE line_num,
                                                   MESSAGE result_text,
                                                   BUFFER buffer)
{
    oss << "[2] Target Subsystem: " << szObjectTypeName << "\n";

    oss << "[3] Querying current Global SACL via AuditQueryGlobalSaclA()...\n";
    BOOLEAN bQueryOriginal = AuditQueryGlobalSaclA(szObjectTypeName, &ppOriginalSD);

    if (bQueryOriginal && pOriginalSD != NULL)
    {
        oss << "  [+] Existing Global SACL retrieved successfully.\n\n";
    }
    else
    {
        SecurityError::Set::handle_no_prior_global_sacl_found_or_query_returned_empty(line_num, result_text, buffer);
    }
}

#endif // METHOD2TARGETOBJECTSUBSYSTEM_HPP