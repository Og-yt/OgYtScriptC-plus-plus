#ifndef OGYTRPCDEF_H
#define OGYTRPCDEF_H

#include <string>
#include <rpc.h>

/* サービスインターフェイス */
typedef const std::string &SVCFUNCNAME;
typedef const std::string &FWINSVCINFC;
typedef const unsigned char CUCSVCINTER;
typedef unsigned short USSVCINTER;
typedef unsigned long ULSVCINTER;
typedef unsigned char UCSVCINTER;
typedef long LSVCINTER;

typedef ULSVCINTER SVCINTER;
typedef ULSVCINTER SVCRESULT;
typedef ULSVCINTER INTERENTRYNAME;

typedef LSVCINTER RPCSTATUS;
typedef LSVCINTER SVCINTERS;

typedef USSVCINTER *PUSSVCINTER;
typedef UCSVCINTER *PUCSVCINTER;
typedef CUCSVCINTER *PCUCSVCINTER;

typedef PUSSVCINTER RPCWENTRYNAME;
typedef PUCSVCINTER RPCENTRYNAME;
typedef PUCSVCINTER PPCAENTRYNAME;
typedef PCUCSVCINTER RCUCSVCINTER;

typedef RPC_BINDING_VECTOR *PRPC_BINDING_VECTOR;

#endif // OGYTRPCDEF_H