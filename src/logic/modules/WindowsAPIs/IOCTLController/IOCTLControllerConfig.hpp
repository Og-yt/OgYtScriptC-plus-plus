#ifndef IOCTLCONTROLLERCONFIG_HPP
#define IOCTLCONTROLLERCONFIG_HPP

#include "_FSCTL_CSV_CONTROL_.hpp"
#include "_FSCTL_CSV_QUERY_DOWN_LEVEL_FILE_SYSTEM_CHARACTERISTICS.hpp"

#include "kernel/IOCTLKernel.hpp"

#include "FSCTL/FSCTL_CreateOrGetObjectIdLogic.hpp"

#include "CreateORGetObjectIDControl.hpp"

#include "VolumePhysicalDiskMitigationIOCtls.hpp"
#include "CreateUSNJournalDataCtls.hpp"
#include "FSCTLCSVQueryDonwLevelFileSystemCharacteristicsCtls.hpp"
#include "FSCTLDeleteObjectIdCtls.hpp"
#include "FSCTLDeleteReparsePointCtls.hpp"
#include "FSCTLDeleteUSNJournalCtls.hpp"
#include "FSCTLDisMountVolumeCtls.hpp"
#include "FSCTLDuplicateExtentsToFileCtls.hpp"
#include "FSCTLEnumUSNDataCtls.hpp"

#endif // IOCTLCONTROLLERCONFIG_HPP