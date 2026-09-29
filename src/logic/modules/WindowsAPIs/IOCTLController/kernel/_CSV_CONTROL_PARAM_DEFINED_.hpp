#ifndef _CSV_CONTROL_PARAM_DEFINED__HPP_
#define _CSV_CONTROL_PARAM_DEFINED__HPP_

typedef enum _CSV_CONTROL_OP
{
    CsvControlStartRedirecting = 1,
    CsvControlStopRedirecting = 2,
    CsvControlQueryRedirectState = 3,
    CsvControlQueryFileRevision = 4,
    CsvControlQueryMdsPath = 5,
    CsvControlQueryFileRevision2 = 6,
    CsvControlPurgeCache = 7,
    CsvControlSetWindowVolume = 8,
    CsvControlClearWindowVolume = 9,
    CsvControlVerifyVolumeRedirected = 10,
    CsvControlAddSiloVolume = 11,
    CsvControlRemoveSiloVolume = 12,
    CsvControlQueryInformation = 13,
    CsvControlSiloVolumeStopRedirecting = 14
} CSV_CONTROL_OP, *PCSV_CONTROL_OP;

typedef struct _CSV_CONTROL_PARAM
{
    CSV_CONTROL_OP Operation;
} CSV_CONTROL_PARAM, *PCSV_CONTROL_PARAM;

#endif // _CSV_CONTROL_PARAM_DEFINED__HPP_