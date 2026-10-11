#ifndef PRINTPERUSERPOLICYMASK_HPP
#define PRINTPERUSERPOLICYMASK_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <string>
#include <sstream>
#include <utility>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../../ToHex.hpp"

MESSAGE PrintPerUserPolicyMask(ULONG ulPolicy, MESSAGE result_text)
{
    std::ostringstream oss;

    const std::pair<ULONG, LPCWSTR> policies[] = {
        { PER_USER_AUDIT_SUCCESS_INCLUDE, L"SUCCESS_INCLUDE" },
        { PER_USER_AUDIT_SUCCESS_EXCLUDE, L"SUCCESS_EXCLUDE" },
        { PER_USER_AUDIT_FAILURE_INCLUDE, L"FAILURE_INCLUDE" },
        { PER_USER_AUDIT_FAILURE_EXCLUDE, L"FAILURE_EXCLUDE" }
    };

    oss << To_16::X8::handle_to_hex_ulong_w(ulPolicy) << L" [ ";

    if (ulPolicy == PER_USER_POLICY_UNCHANGED)
    {
        oss << L"PER_USER_POLICY_UNCHANGED ";
    }
    else if (ulPolicy == PER_USER_AUDIT_NONE)
    {
        oss << L"PER_USER_AUDIT_NONE (No overrides) ";
    }
    else
    {
        for (const auto& [flag, name] : policies)
        {
            if (ulPolicy & flag)
            {
                oss << name;
            }
        }
    }

    oss << L"]";
    return result_text += oss.str();
}

#endif // PRINTPERUSERPOLICYMASK_HPP