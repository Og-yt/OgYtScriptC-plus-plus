#ifndef CREATEFILEWCONTROLLER_HPP
#define CREATEFILEWCONTROLLER_HPP

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00 // Windows 10 / 11

#include <gtkmm.h>

#include <windows.h>

/**
 * 
 * 
 * @param 第1引数 関数コード [ 0:  ]
 * 
 * 
 * 
 */
inline bool CreateFileWController(DWORD function_code,
                                  HANDLE hFile,
                                  LPCWSTR target_path,
                                  DWORD general_access_rights,
                                  DWORD file_access_rights,
                                  DWORD creationDisposition,
                                  DWORD dwAttribute)
{
    if (function_code == 0)
    {
        //
    }
    else if (function_code == 1)
    {
        //
    }
    else if (function_code == 2)
    {
        //
    }
}

#endif // _WIN32_WINNT
#endif // CREATEFILECONTROLLER_HPP