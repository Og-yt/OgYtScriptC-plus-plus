#ifndef PRINTAUDITPOLICYFLAGS_HPP
#define PRINTAUDITPOLICYFLAGS_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>
#include <string>
#include "../../ToHex.hpp"

namespace AuditPolicyFlag
{
    inline void handle_audit_query_per_user_policy_print_audit_policy_flags(ULONG policyFlags, std::string &result_text)
    {
        std::ostringstream oss;

        if (policyFlags == POLICY_AUDIT_EVENT_UNCHANGED)
        {
            oss << "Unchanged / Not Set";
        }
        else if (policyFlags == POLICY_AUDIT_EVENT_NONE)
        {
            oss << "No Auditing";
        }
        else
        {
            if (policyFlags & POLICY_AUDIT_EVENT_SUCCESS)
            {
                oss << "[Success] ";
            }
            if (policyFlags & POLICY_AUDIT_EVENT_FAILURE)
            {
                oss << "[Failure] ";
            }
        }

        oss << "\n";
        result_text += oss.str();
    }

    inline void handle_audit_query_system_policy_print_audit_policy_flags(ULONG auditPolicy, std::string &result_text)
    {
        std::ostringstream oss;

        oss << "0x" << To_16::handle_to_hex_ulong(auditPolicy, 1) << " [ ";

        if (auditPolicy == POLICY_AUDIT_EVENT_UNCHANGED)
        {
            oss << "AUDIT_POLICY_UNCHAGED ";
        }
        else if (auditPolicy == POLICY_AUDIT_EVENT_FAILURE)
        {
            oss << "AUDIT_POLICY_FAILURE (None) ";
        }
        else
        {
            if (auditPolicy & POLICY_AUDIT_EVENT_SUCCESS)
            {
                oss << "SUCCESS ";
            }
            if (auditPolicy & POLICY_AUDIT_EVENT_FAILURE)
            {
                oss << "FAILURE ";
            }
        }

        oss << "]";
        result_text += oss.str();
    }
}

#endif // PRINTAUDITPOLICYFLAGS_HPP