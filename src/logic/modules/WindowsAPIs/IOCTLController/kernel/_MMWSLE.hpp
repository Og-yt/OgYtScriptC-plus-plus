#ifndef _MMWSLE_HPP
#define _MMWSLE_HPP

struct _MMWSLE
{
    ULONG FirstFree;
    ULONG FirstDynamic;
    ULONG LastEntry;
    ULONG NextSlot;
    PMMWSLE Wsle;
    PVOID LowestPagableAddress;
    ULONG LastInitializedWsle;
    ULONG NextEstimationSlot;
    ULONG NextAgingSlot;
    ULONG EstimatedAvailable;
    ULONG GrowthSinceLastEstimate;
    ULONG NumberOfCommittedPageTables;
    ULONG VadBitMapHint;
    ULONG NonDirectCount;
    PMMWSLE_NONDIRECT_HASH NonDirectHash;
    PMMWSLE_HASH HashTableStart;
    PMMWSLE_HASH HighestPermittedHashAddress;
    PVOID HighestUserAddress;
    WORD UsedPageTableEntries[1536];
    ULONG CommittedPageTables[48];
};

#endif // _MMWSLE_HPP