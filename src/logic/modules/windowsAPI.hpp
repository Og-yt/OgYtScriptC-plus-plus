#ifndef WINDOWSAPI_HPP
#define WINDOWSAPI_HPP

#include <gtkmm.h>
#include <windows.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include "../ErrorLogic.hpp"
#include "WindowsAPIs/HardWareControls.hpp"      // ハードウェアの情報を取得
#include "WindowsAPIs/PhysicalBoradControls.hpp" // 物理ボードの情報を取得
#include "WindowsAPIs/RAMControls.hpp"           // メモリ操作
#include "WindowsAPIs/RegistryControls.hpp"      // レジストリ操作
#include "WindowsAPIs/ServiceControls.hpp"       // サービス操作
#include "WindowsAPIs/MessageBoxCreate.hpp"      // メッセージボックスの出力
#include "WindowsAPIs/System.hpp"                // コマンドプロンプト
#include "WindowsAPIs/IOControls.hpp"            // 特殊な操作
#include "WindowsAPIs/MouseControls.hpp"         // カーソルコントロール
#include "WindowsAPIs/TaskSchedulerControls.hpp" // タスクスケジューラサービスの使用
#include "WindowsAPIs/Security.hpp"              // セキュリティ操作

#endif // WINDOWSAPI_HPP