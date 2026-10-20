#ifndef LSAWUERYDOMAININFORMATIONPOLICY_HPP
#define LSAWUERYDOMAININFORMATIONPOLICY_HPP

#include "SecuritySet.hpp"

inline bool handle_lsa_query_domain_information_policy_sub_func(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer)
{
    std::ostringstream oss;

    LSA_OBJECT_ATTRIBUTES attr = {};

    if (attr.Length == NULL)
    {
        return 0;
    }

    attr.Length = sizeof(attr);

    LSA_HANDLE lHandle = NULL;
    NTSTATUS status = LsaOpenPolicy(NULL, &attr, POLICY_VIEW_LOCAL_INFORMATION, &lHandle);

    PVOID pbuffer = NULL;

    if (CUSTOM_NT_SUCCESS(status))
    {
        status = LsaQueryDomainInformationPolicy(lHandle, PolicyDomainEfsInformation, &pbuffer);

        if (CUSTOM_NT_SUCCESS(status))
        {
            LsaFreeMemory(lHandle);
        }

        LsaClose(lHandle);
    }

    result_text += oss.str();
    return true;
}



#endif // LSAWUERYDOMAININFORMATIONPOLICY_HPP