#ifndef LSAWUERYDOMAININFORMATIONPOLICY_HPP
#define LSAWUERYDOMAININFORMATIONPOLICY_HPP

#include "SecuritySet.hpp"

inline bool handle_lsa_query_domain_information_policy_sub_func(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer)
{
    std::ostringstream oss;
    LSA_HANDLE lHandle;
    PVOID pbuffer;

    NTSTATUS status = LsaQueryDomainInformationPolicy(lHandle, POLICY_DOMAIN_INFORMATION_CLASS::PolicyDomainEfsInformation, &pbuffer);
    if (!CUSTOM_NT_SUCCESS(status))
    {
        //
    }

    result_text += oss.str();
    return true;
}



#endif // LSAWUERYDOMAININFORMATIONPOLICY_HPP