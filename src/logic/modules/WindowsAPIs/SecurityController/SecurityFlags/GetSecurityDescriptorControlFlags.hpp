#ifndef GETSECURITYDESCRIPTORCONTROLFLAGS_HPP
#define GETSECURITYDESCRIPTORCONTROLFLAGS_HPP

#include <windows.h>
#include <string>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_get_security_descriptor_control_flags(SECURITY_DESCRIPTOR_CONTROL control,
                                                         std::string &result_text)
{
    result_text += "\n--- Security Descriptor Control Flags ---\n";
    result_text += "Self-Relative Format:  " + ((control & SE_SELF_RELATIVE) ? 'YES' : 'NO (Absolute)\n');
    result_text += "DACL Present:          " + ((control & SE_DACL_PRESENT) ? 'YES' : 'NO (Null DACL / No Access Control)\n');

    if (control & SE_DACL_PRESENT)
    {
        result_text += "DACL Defauled:        " + ((control & SE_DACL_DEFAULTED) ? 'YES' : 'NO\n');
        result_text += "DACL Protected:        " + ((control & SE_DACL_PROTECTED) ? 'YES' : 'NO\n');
        result_text += "DACL Auto-Inherited:   " + ((control & SE_DACL_AUTO_INHERITED) ? 'YES' : 'NO\n');
    }

    result_text += "SACL Present:          " + ((control & SE_SACL_PRESENT) ? 'YES' : 'NO\n');

    if (control & SE_SACL_PRESENT)
    {
        result_text += "SACL Protected:        " + ((control & SE_SACL_PROTECTED) ? 'YES' : 'NO\n');
        result_text += "SACL Auto-Inherited:   " + ((control & SE_SACL_AUTO_INHERITED) ? 'YES' : 'NO\n');
    }

    result_text += "RM Control Valid:      " + ((control & SE_RM_CONTROL_VALID) ? 'YES' : 'NO\n');

    return true;
}

#endif // GETSECURITYDESCRIPTORCONTROLFLAFS_HPP