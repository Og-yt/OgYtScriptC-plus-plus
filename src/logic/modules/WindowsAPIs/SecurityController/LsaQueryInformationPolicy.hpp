#ifndef LSAQUERYINFORMATIONPOLICY_HPP
#define LSAQUERYINFORMATIONPOLICY_HPP

#include "SecuritySet.hpp"
#include "PolicyInformationClass/PolicyInformationClasses.hpp"

inline bool handle_lsa_query_information_policy_sub_func(POLICYINF policyInfo,
                                                         LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer)
{
    std::ostringstream oss;
    LSA_HANDLE lHandle = NULL;
    LSA_OBJECT_ATTRIBUTES attr = {};

    if (attr.Length == NULL)
    {
        return 0;
    }

    attr.Length = sizeof(attr);

    NTSTATUS status = LsaOpenPolicy(NULL, &attr, PolicyDomainEfsInformation, &lHandle);

    if (CUSTOM_NT_SUCCESS(status))
    {
        PVOID pbuffer;

        status = LsaQueryInformationPolicy(lHandle, PolicyInformationClassEnumerator(policyInfo), &pbuffer);
        if (!CUSTOM_NT_SUCCESS(status))
        {
            LsaClose(lHandle);
        }

        LsaFreeMemory(lHandle);
    }

    result_text += oss.str();
    return false;
}

#endif // LSAQUERYINFORMATIONPOLICY_HPP