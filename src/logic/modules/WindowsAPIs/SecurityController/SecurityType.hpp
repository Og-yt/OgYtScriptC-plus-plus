#ifndef SECURITYTYPE_HPP
#define SECURITYTYPE_HPP

#include <windows.h>
#include <string>
#include <vector>
#include <utility>

typedef std::vector<BYTE> SIDBUF;
typedef std::vector<GUID> TAGSUBCAT;
typedef std::vector<std::wstring> SUBCATNAME;

#endif // SECURITYTYPE_HPP