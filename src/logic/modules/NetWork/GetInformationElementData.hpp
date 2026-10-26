#ifndef GETINFORMATIONELEMENTDATA_HPP
#define GETINFORMATIONELEMENTDATA_HPP

#include <windows.h>
#include <wlanapi.h>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool GetInformationElementData(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    PWLAN_BSS_LIST pBssList = NULL;

    if (pBssList != NULL && pBssList->dwNumberOfItems > 0)
    {
        const WLAN_BSS_ENTRY &entry = pBssList->wlanBssEntries[0];
        const BYTE *base = reinterpret_cast<const BYTE *>(pBssList);
        const size_t totalSize = pBssList->dwTotalSize;

        if (entry.ulIeOffset <= totalSize &&
            entry.ulIeSize <= totalSize - entry.ulIeOffset &&
            entry.ulIeSize > 0)
        {
            const BYTE *pRawIeData = base + entry.ulIeSize;
            DWORD dwIeDataSize = entry.ulIeSize;
        }
    }

    if (pBssList != NULL)
    {
        WlanFreeMemory(pBssList);
    }
}

#endif // GETINFORMATIONELEMENTDATA_HPP