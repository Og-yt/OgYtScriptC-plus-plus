#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include <gtkmm.h>
#include <map>
#include <string>
#include <exception>
#include <windows.h>         // レジストリ、ハードウェア操作、ビープ管理
#include "importError/importError.hpp"           // importError
#include "SUCCESS/SUCCESS.hpp"
#include "ArrayError/ArrayError.hpp"             // Array
#include "MathError/MathError.hpp"               // Math
#include "MosquitoError/MosquitoError.hpp"       // Mosquito
#include "WinAPIError/WinAPIError.hpp"           // Windows Function
#include "AutoScriptError/AutoScriptError.hpp"   // AutoScript
#include "ThreadError/ThreadError.hpp"           // Thread
#include "PythonError/PythonError.hpp"           // Python
#include "../ErrorLogic.hpp"                     // ErrorMessageIO

#endif // MESSAGES_HPP