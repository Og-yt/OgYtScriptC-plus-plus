#ifndef OGYTRPCDEF_H
#define OGYTRPCDEF_H

#include <string>
#include <rpc.h>

/* サービスインターフェイス */
typedef void VRPCHANDLE;

typedef const std::string &SVCFUNCNAME;
typedef const std::string &FWINSVCINFC;
typedef const unsigned char CUCSVCINTER;
typedef unsigned short USSVCINTER;
typedef unsigned long ULSVCINTER;
typedef unsigned char UCSVCINTER;
typedef long LSVCINTER;

/* unsigned long */
typedef ULSVCINTER SVCINTER;
typedef ULSVCINTER SVCRESULT;
typedef ULSVCINTER INTERENTRYNAME;

/* long */
typedef LSVCINTER RPCSTATUS;
typedef LSVCINTER SVCINTERS;

typedef USSVCINTER *PUSSVCINTER;
typedef UCSVCINTER *PUCSVCINTER;
typedef CUCSVCINTER *PCUCSVCINTER;

/**
 * 
 * unsigned short *
 * 
 */
typedef PUSSVCINTER RPCWENTRYNAME;
typedef PUSSVCINTER RPCSTRINGBIND;

/* unsigned char * */
typedef PUCSVCINTER RPCENTRYNAME;
typedef PUCSVCINTER PPCAENTRYNAME;

/* const unsigned char * */
typedef PCUCSVCINTER RCUCSVCINTER;

/* void * */
typedef VRPCHANDLE *RPCHANDLE;

typedef RPC_BINDING_VECTOR *PRPC_BINDING_VECTOR;

#endif // OGYTRPCDEF_H