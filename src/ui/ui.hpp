#ifndef UI_HPP
#define UI_HPP

#include <gtkmm.h>
#include <regex>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include "../logic/ErrorLogic.hpp"
#include "../logic/Interpreter/InterpreterLogic.hpp"
#include "../logic/Interpreter/ControlSyntaxLogic.hpp"
#include "../logic/modules/importConfig.hpp"
#include "../logic/Integration/pythonBridge.hpp"
// #include "../logic/onClick.hpp"

typedef InterpreterLogic::Variables VARIABLE;

class MainWindow : public Gtk::Window
{
public:
    MainWindow()
    {
        set_title("OgYtScriptC++");
        set_default_size(800, 600);

        // main content
        box.set_orientation(Gtk::Orientation::VERTICAL);

        // top content
        top_box.add_css_class("top-container");
        top_box.set_size_request(-1, 40);
        auto top_label = Gtk::make_managed<Gtk::Label>("Toolbar / Menu Area");
        top_box.append(*top_label);
        box.append(top_box);

        run_button.set_label("Run Code");
        run_button.set_margin_start(20);
        run_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_run_clicked));
        top_box.append(run_button);

        // center content (left editor)
        mid_box.set_orientation(Gtk::Orientation::HORIZONTAL);
        mid_box.set_expand(true);

        // left content
        left_box.set_orientation(Gtk::Orientation::HORIZONTAL);
        left_box.set_size_request(150, -1);
        left_box.add_css_class("left-container");
        auto left_label = Gtk::make_managed<Gtk::Label>("Project Tree");
        left_box.append(*left_label);
        mid_box.append(left_box);

        // center content (TextView)
        scrolled_window.set_child(txtbox);
        scrolled_window.set_policy(Gtk::PolicyType::AUTOMATIC,
                                   Gtk::PolicyType::AUTOMATIC);
        scrolled_window.add_css_class("text-box-container");
        scrolled_window.set_expand(true);
        mid_box.append(scrolled_window);

        // ハイライトのセットアップ
        buffer = txtbox.get_buffer();
        setup_tags();
        buffer->signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_buffer_changed));

        box.append(mid_box);

        // bottom content
        bottom_box.add_css_class("bottom-container");
        bottom_box.set_size_request(-1, 40);
        console_output.set_text("Console: Ready");
        console_output.set_margin_start(10);
        console_output.set_halign(Gtk::Align::START);
        bottom_box.append(console_output);
        box.append(bottom_box);

        set_child(box);

        // CSS の適用
        apply_css();
    }

private:
    Gtk::Box box;
    Gtk::Box top_box;
    Gtk::Box mid_box;
    Gtk::Box left_box;
    Gtk::Box bottom_box;
    Gtk::TextView txtbox;
    Gtk::ScrolledWindow scrolled_window;
    Glib::RefPtr<Gtk::TextBuffer> buffer;
    Gtk::Button run_button;
    Gtk::Label console_output;

    // Member function declarations
    void setup_tags()
    {
        auto tag_keyword = buffer->create_tag("keyword");
        tag_keyword->property_foreground() = "#569cd6";
        tag_keyword->property_weight() = Pango::Weight::BOLD;

        auto tag_special = buffer->create_tag("special");
        tag_special->property_foreground() = "#4EC9B0";

        auto tag_control = buffer->create_tag("control");
        tag_control->property_foreground() = "#C586C0";

        auto tag_string = buffer->create_tag("string");
        tag_string->property_foreground() = "#ce9178";

        auto tag_comment = buffer->create_tag("comment");
        tag_comment->property_foreground() = "#6a9955";
        tag_comment->property_weight() = Pango::Weight::BOLD;

        auto tag_bracket0 = buffer->create_tag("bracket0");
        tag_bracket0->property_foreground() = "#ffd700";
        tag_bracket0->property_weight() = Pango::Weight::BOLD;

        auto tag_bracket1 = buffer->create_tag("bracket1");
        tag_bracket1->property_foreground() = "#da70d6";
        tag_bracket1->property_weight() = Pango::Weight::BOLD;

        auto tag_bracket2 = buffer->create_tag("bracket2");
        tag_bracket2->property_foreground() = "#179fff";
        tag_bracket2->property_weight() = Pango::Weight::BOLD;

        auto tag_bracket999 = buffer->create_tag("bracket999");
        tag_bracket999->property_foreground() = "#9cdcfe";

        auto tag_function = buffer->create_tag("function");
        tag_function->property_foreground() = "#dcdcaa";

        auto tag_number = buffer->create_tag("number");
        tag_number->property_foreground() = "#b5cea8";

        auto tag_default = buffer->create_tag("default");
        tag_default->property_foreground() = "#ffffff";

        // エラー背景用のタグ (暗めの赤)
        auto tag_error = buffer->create_tag("error_bg");
        tag_error->property_background() = "#4b1818";
    }

    void on_buffer_changed()
    {
        auto start = buffer->begin();
        auto end = buffer->end();
        buffer->remove_all_tags(start, end);

        Glib::ustring text = buffer->get_text();
        std::string raw_text = text.raw();

        // キーワード (Blue: #569cd6)
        std::regex keyword_re("\\b(int|uint|sint|double|udouble|sdouble|string|Array|float|ufloat|sfloat|long|ulong|slong|long long|ulong long|slong long|short|ushort|sshort|char|noexcept|override|Oclass|public|private|assemble|static|void|NULL|to_String|to_Int|to_double|HKEY_CLASSES_ROOT|HKEY_CURRENT_USER|HKEY_LOCAL_MACHINE|HKEY_USERS|HKEY_CURRENT_CONFIG|DISKPART|CMD|function|const|let|var|SELECT|AS|CURSOR|UNION|TABLE)\\b");

        // スペシャル (Green: #4ec9b0)
        std::regex special_re("\\b(!|sInp|input|HTML|CSS|JavaScript|SQL|BAT|OGPS_1|BigInt|BigBase|Regex|BIN|OCT|HEX|to_BIN|to_OCT|to_HEX|__Base_num_[3-9]__|__Big__Base_num_[3-9]__|__Base_num_[1-5][0-9]__|__Big__Base_num_[1-5][0-9]__|__Base_num_6[0-2]__|__Big_Base_num_6[0-2]__|exception|showHTML|document|MosqSoundStart|MosqSoundStop|DOREMI|AutoScript|misleep|ssleep|msleep|hsleep|Python)\\b");

        // 制御文 (Purple: #C586C0)
        std::regex control_re("\\b(if|else|elif|endif|EQU|NEQ|AND|OR|NOT|XOR|0A|0V|IA|IV|for|endfor|while|endwhile|do|enddo|switch|endswitch|case|break|continue|default|try|endtry|catch|INFINITY|return|import|KEY_READ|KEY_WRITE|KEY_ALL_ACCESS|def|forEach|Oclass|CLASS|id|ID|bool|true|false)\\b");

        std::regex string_re("(\".*?\")|(\'.*?\')");
        std::regex comment_re("//.*");
        std::regex ternary_op_re("[\\?\\:]"); // 三項演算子の記号 ? と :
        std::regex var_basic_re("\\b(div|span|p|html|head|body|title|table|thead|tbody|tfooter|th|tr|td|button|ol|ul|al|li)\\b");
        // 変数宣言のハイライト (最後の空のパイプ | を削除)
        std::regex var_decl_re("\\b(int|uint|sint|string|bool|double|udouble|sdouble|float|ufloat|sfloat|long long|long|ulong long|slong long|ulong|slong|short|ushort|sshort|char|HTML|CSS|JavaScript|BigInt|Regex|BIN|OCT|HEX|__Base_num_[3-9]__|__Base_num_[1-5][0-9]__|__Base_num_6[0-2]__|AutoScript|SQL|Array)\\s+([a-zA-Z_][a-zA-Z0-9_]*)");
        std::regex class_re("\\b(Oclass|CLASS)\\s+([a-zA-Z_][a-zA-Z0-9_]*)");
        std::regex struct_re("\\b(struct|TABLE)\\s+([a-zA-Z_][a-zA-Z0-9_]*)");
        std::regex func_re("\\b(print|println|c_str)\\b"); // 特定の関数のみハイライトを適用
        std::regex number_re("\\b(0x[0-9a-fA-F]+|\\d+\\.?\\d*)\\b");

        // Math型
        std::regex math_re("\\b(MathSin|MathCos|MathTan|MathASin|MathACos|MathATan|MathSqrt|MathCbrt|MathLog[2-9]|MathLog[1][1-6]|MathPower|MathFact|MathE|MathPI|MathPower[2-5]|MathPermutation|MathCombination|MathIntegral|MathDoubleIntegral|MathTripleIntegral|MathTetraIntegral|MathPentaIntegral|Math[1-4]EQT|MathPhi|MathMobius|MathDiv0|MathDiv1|MathDivS|MathPrime|MathExtGCD|MathBell|MathGamma|MathCatalan|MathECatalan|MathFibonacci|MathLucas|MathAAiry|MathBAiry|MathDwIntegral|MathFreIntegral|MathClausen|MathLerTransc|MathPolyLog|MathHWzeta|MathBarnesInteger|MathBarnesReal|MathDigamma|MathTrigamma|MathPolygamma|MathWeiss|MathJacoSN|MathJacoDN|MathWeissP|MathJacoT1)\\b");

        // windows関連
        std::regex windows_re("\\b(RegCreateKeyExA|RegOpenKeyExA|RegCloseKey|RegDeleteKeyExA|RegSetValueExA|RegQueryValueExA|WinCreateMsgBox|GTKCreateMsgBox|HWGetMemoryInfo|HWGetCPUCoreInfo|PBGetDiskInfo|PBGetLogicalDriveInfo|NetGetIPAddress|GetGlobalMemoryInfo|GetMemoryUsageInfo|GetTotalRAMInfo|GetAvailabelRAMInfo|GetTotalPageFileInfo|GetAvailabelPageFileInfo|GetAvailabelVirtualMemorySizeInfo|GetTotalVirtualMemorySizeInfo|GetAvailabelExtendedVirtualMemorySizeInfo|GetMemoryInformationCode|GetOgYtScriptMemoryUsageInfo|OpenServiceManager|GetServiceInfo|OpenCommand|CreateMsgBox|VolPysDiskMitigationIO|CreateORGetObjectID|CreateUSNJournalData|GetCSVLocalNodeControl|FSCTLDeleteObjectId|FSCTLDeleteUSNJournal|SetCursorPosition|GetCurrentCursorPosition|ExSetCursorPosition|CtrlKeyControl|Command)\\b");

        // AutoScript関連
        std::regex auto_script_re("\\b(CtrlKeyControl|ShiftKeyControl|WindowsKey|AltKeyControl|EscapeKeyControl|MouseControlSetCursorPositionN|OpenCMD)\\b");

        /* time関連 & 国コード(3桁)  */
        std::regex time_re("\\b(CurrentTime|CurrentWorldTime)\\b");
        std::regex country_code_re("\\b(MID|NIU|ASM|USA_HL|COK_RAR|PYF|USA_ANC|GMD|USA_LOS|PCN|USA_CAM|USA_CHI|ECW|USA_NEW|EASTER|USA_CAR|BMU|ARG|SGS|CPV|CIV|GBR|ITA|GRC|KEN|RUS_MOS|IRQ|UAE|PAK|BGD|IDN|CHN|JPN|GUM|RUS_SAK|NRU)\\b");

        auto apply_style = [&](const std::regex &re, const std::string &tag_name)
        {
            auto words_begin = std::sregex_iterator(raw_text.begin(), raw_text.end(), re);
            auto words_end = std::sregex_iterator();

            for (std::sregex_iterator i = words_begin; i != words_end; ++i)
            {
                std::smatch match = *i;
                auto m_start = buffer->get_iter_at_offset(match.position());
                auto m_end = buffer->get_iter_at_offset(match.position() + match.length());
                buffer->apply_tag_by_name(tag_name, m_start, m_end);
            }
        };

        apply_style(keyword_re, "keyword");
        apply_style(string_re, "string");
        apply_style(special_re, "special");
        apply_style(control_re, "control");    // 制御文を適用
        apply_style(ternary_op_re, "control"); // 三項演算子の記号をハイライト
        apply_style(func_re, "function");
        apply_style(number_re, "number");
        apply_style(comment_re, "comment");
        apply_style(var_basic_re, "bracket999");
        apply_style(class_re, "special");
        apply_style(struct_re, "keyword");
        apply_style(math_re, "special");
        apply_style(windows_re, "special");
        apply_style(auto_script_re, "special");
        apply_style(time_re, "special");
        apply_style(country_code_re, "keyword");

        // 型の後に続く変数名をハイライト (キャプチャグループ 2 を使用)
        auto decl_begin = std::sregex_iterator(raw_text.begin(), raw_text.end(), var_decl_re);
        auto decl_end = std::sregex_iterator();
        for (std::sregex_iterator i = decl_begin; i != decl_end; ++i)
        {
            std::smatch match = *i;
            auto m_start = buffer->get_iter_at_offset(match.position(2));
            auto m_end = buffer->get_iter_at_offset(match.position(2) + match.length(2));
            buffer->apply_tag_by_name("bracket999", m_start, m_end);
        }

        int depth = 0;
        std::vector<std::string> active_bracket_tags; // 開きかっこで使ったタグを保持するスタック

        for (auto it = buffer->begin(); it != buffer->end(); ++it)
        {
            gunichar c = *it;
            if (!it.get_tags().empty())
                continue;

            if (c == '{' || c == '[' || c == '(')
            {
                std::string tag_name;
                if (c == '(')
                {
                    // 直前の単語を確認してif, for, while なら紫色、それ以外なら黄色にする
                    auto check_it = it;

                    // 空白を読み飛ばす
                    while (check_it != buffer->begin())
                    {
                        auto prev = check_it;
                        --prev;

                        if (g_unichar_isspace(*prev))
                        {
                            check_it = prev;
                        }
                        else
                        {
                            break;
                        }
                    }

                    // 単語の開始位置を探す
                    auto word_end = check_it;
                    auto word_start = check_it;

                    while (word_start != buffer->begin())
                    {
                        auto prev = word_start;
                        --prev;

                        if (g_unichar_isalnum(*prev) || *prev == '_')
                        {
                            word_start = prev;
                        }
                        else
                        {
                            break;
                        }
                    }

                    Glib::ustring word = buffer->get_text(word_start, word_end);
                    tag_name = (word == "if" ||
                                word == "for" ||
                                word == "while")
                                   ? "control"
                                   : "bracket0";
                }
                else
                {
                    // {} や [] は既存のレインボーロジックを適用
                    tag_name = "bracket" + std::to_string(depth % 3);
                }

                auto next_it = it;
                ++next_it;
                buffer->apply_tag_by_name(tag_name, it, next_it);
                active_bracket_tags.push_back(tag_name); // 使ったタグをスタックに保存
                depth++;
            }
            else if (c == '}' || c == ']' || c == ')')
            {
                depth = std::max(0, depth - 1);
                std::string tag_name = "bracket0"; // default
                if (!active_bracket_tags.empty())
                {
                    tag_name = active_bracket_tags.back(); // 開いた時と同じ色を取得
                    active_bracket_tags.pop_back();
                }
                auto next_it = it;
                ++next_it;
                buffer->apply_tag_by_name(tag_name, it, next_it);
            }
            else
            {
                // ブラケット以外の文字かつ、他のタグ（キーワード等）が適用されていない場合に白い文字を適用
                auto next_it = it;
                ++next_it;
                buffer->apply_tag_by_name("default", it, next_it);
            }
        }
    }

    void on_run_clicked()
    {
        std::string code = buffer->get_text();
        std::stringstream ss(code);
        std::string line;
        InterpreterLogic::Variables variables;
        auto &vars = variables.int_vars;
        auto &uint_vars = variables.uint_vars;
        auto &sint_vars = variables.sint_vars;
        auto &ulong_vars = variables.ulong_vars;
        auto &slong_vars = variables.slong_vars;
        auto &ulong_long_vars = variables.ulong_long_vars;
        auto &slong_long_vars = variables.slong_long_vars;
        auto &ushort_vars = variables.ushort_vars;
        auto &sshort_vars = variables.sshort_vars;
        auto &str_vars = variables.string_vars;
        auto &double_vars = variables.double_vars;
        auto &float_vars = variables.float_vars;
        auto &short_vars = variables.short_vars;
        auto &bool_vars = variables.bool_vars;
        auto &long_vars = variables.long_vars;
        auto &long_long_vars = variables.long_long_vars;
        ArrayVariables::Store array_store;
        std::string resultText = "";
        int lineCount = 0;
        bool array_imported = false;
        bool programmer_imported = false;
        bool mosquito_sound_imported = false;
        bool windows_api_imported = false;
        bool vector_imported = false;
        bool algorithm_imported = false;
        bool math_imported = false;
        bool system_imported = false;
        bool time_imported = false;
        bool auto_script_imported = false;
        bool thread_imported = false;
        bool python_imported = false;
        std::map<std::string, std::string> auto_scripts;

        ErrorLogic::clear_highlights(buffer);

        while (std::getline(ss, line))
        {
            lineCount++;

            // 行全体のトリミングとコメント除去
            size_t start = line.find_first_not_of(" \t\r\n");
            if (start == std::string::npos)
                continue;

            line = line.substr(start);

            // 行内コメント (//) を除去
            size_t comment_pos = line.find("//");
            if (comment_pos != std::string::npos)
            {
                line = line.substr(0, comment_pos);
            }

            if (line.empty() || line.substr(0, 2) == "//")
            {
                continue;
            }
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line.find("import") == 0)
            {
                if (line.find("\"Array\"") != std::string::npos)
                {
                    array_imported = true;
                }
                else if (line.find("\"programmer\"") != std::string::npos)
                {
                    programmer_imported = true;
                }
                else if (line.find("\"Mosquito\"") != std::string::npos)
                {
                    mosquito_sound_imported = true;
                }
                else if (line.find("\"windows\"") != std::string::npos)
                {
                    windows_api_imported = true;
                }
                else if (line.find("\"vector\"") != std::string::npos)
                {
                    vector_imported = true;
                }
                else if (line.find("\"algorithm\"") != std::string::npos)
                {
                    algorithm_imported = true;
                }
                else if (line.find("\"math\"") != std::string::npos)
                {
                    math_imported = true;
                }
                else if (line.find("\"System\"") != std::string::npos)
                {
                    system_imported = true;
                }
                else if (line.find("\"time\"") != std::string::npos)
                {
                    time_imported = true;
                }
                else if (line.find("\"AutoScript\"") != std::string::npos)
                {
                    auto_script_imported = true;
                }
                else if (line.find("\"thread\"") != std::string::npos)
                {
                    thread_imported = true;
                }
                else if (line.find("\"python\"") != std::string::npos)
                {
                    python_imported = true;
                }
                continue;
            }
            else if (line.find("AutoScript") == 0)
            {
                if (!auto_script_imported)
                {
                    resultText += ErrorLogic::build_msg(lineCount, "AutoScript import is required.", true);
                    ErrorLogic::highlight_line(buffer, lineCount);
                    break;
                }

                static const std::regex auto_script_re(
                    R"(^AutoScript\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*\(\s*$)");
                std::smatch auto_script_match;

                if (!std::regex_match(line, auto_script_match, auto_script_re))
                {
                    resultText += ErrorLogic::build_msg(lineCount, "Invalid AutoScript declaration.", true);
                    ErrorLogic::highlight_line(buffer, lineCount);
                    break;
                }

                const std::string script_name = auto_script_match[1].str();
                std::string script_body;
                std::string body_line;
                bool closed = false;

                while (std::getline(ss, body_line))
                {
                    lineCount++;

                    const size_t body_start =
                        body_line.find_first_not_of(" \t\r\n");
                    if (body_start == std::string::npos)
                    {
                        continue;
                    }

                    body_line = body_line.substr(body_start);
                    const size_t body_end =
                        body_line.find_last_not_of(" \t\r\n");
                    body_line.erase(body_end + 1);

                    if (body_line == ");")
                    {
                        closed = true;
                        break;
                    }

                    if (body_line.rfind("int", 0) == 0)
                    {
                        if (!InterpreterLogic::INT::handle_int_decl(
                                body_line, vars, lineCount, resultText, buffer,
                                windows_api_imported))
                        {
                            break;
                        }
                    }
                    else if (body_line.rfind("print", 0) == 0)
                    {
                        if (!InterpreterLogic::PRINT::handle_print(
                                body_line, vars, str_vars, double_vars,
                                float_vars, long_long_vars, ulong_long_vars,
                                slong_long_vars, long_vars, ulong_vars,
                                slong_vars, uint_vars, sint_vars, short_vars,
                                ushort_vars, sshort_vars, bool_vars, lineCount,
                                resultText, buffer, auto_script_imported))
                        {
                            break;
                        }
                    }
                    else if (body_line.rfind("MouseControlSetCursorPositionN", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_mouse_control_set_cursor_position_n(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("MouseControlLeftOnClick", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_mouse_control_left_on_click(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("MouseControlLeftDoubleClick", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_mouse_control_left_double_click(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("MouseControlRightOnClick", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_mouse_control_right_on_click(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("MouseControlRightDoubleClick", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_mouse_control_right_double_click(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("ShowCursor", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_mouse_control_show_cursor(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("GetCursorAddressHandle", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_get_cursor_address_handle(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("SetPhysicalCursorPosition", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_set_physical_cursor_position(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("SetMousePointerSpeed", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_set_mouse_pointer_speed(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("ResetMousePointerSpeed", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::MouseControl::handle_reset_mouse_pointer_speed(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("CtrlKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Ctrl::handle_ctrl_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("ShiftKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Shift::handle_shift_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("CtrlShiftKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Ctrl_Shift::handle_ctrl_shift_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("WindowsKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Windows::handle_windows_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("CtrlWindowsKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Ctrl_Windows::handle_ctrl_windows_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("CtrlShiftWindowsKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Ctrl_Shift_Windows::handle_ctrl_shift_windows_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("AltKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Alt::handle_alt_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("ShiftAltKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Shift_Alt::handle_shift_alt_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("CtrlAltKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Ctrl_Alt::handle_ctrl_alt_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("EscapeKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Escape::handle_escape_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("AltTabKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::AltTab::handle_alt_tab_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("ShiftCapsLockKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Shift_CapsLock::handle_shift_caps_lock_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("TabKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Tab::handle_tab_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("CapsLockKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::CapsLock::handle_caps_lock_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("InsertKeyControl", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::KeyBoardControl::Insert::handle_insert_key_control(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else if (body_line.rfind("OpenCMD", 0) == 0)
                    {
                        OgYtAutomaticControlBatchScripts::CommandControl::handle_open_cmd(
                            body_line, lineCount, resultText, buffer, auto_script_imported);
                    }
                    else
                    {
                        resultText += ErrorLogic::build_msg(
                            lineCount,
                            "Unknown AutoScript command '" + body_line + "'",
                            true);
                        ErrorLogic::highlight_line(buffer, lineCount);
                        break;
                    }

                    script_body += body_line + "\n";
                }

                if (!closed)
                {
                    resultText += ErrorLogic::build_msg(
                        lineCount, "Expected ');' to close AutoScript.", true);
                    ErrorLogic::highlight_line(buffer, lineCount);
                    break;
                }

                auto_scripts[script_name] = script_body;
            }
            else if (line.find("Python") == 0)
            {
                if (!python_imported)
                {
                    resultText += ErrorLogic::build_msg(lineCount, "Python import is required.", true);
                    ErrorLogic::highlight_line(buffer, lineCount);
                    break;
                }

                static const std::regex python_re(
                    R"(^Python\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*\(\s*$)");
                std::smatch python_match;

                if (!std::regex_match(line, python_match, python_re))
                {
                    resultText += ErrorLogic::build_msg(lineCount, "Invalid Python declaration.", true);
                    ErrorLogic::highlight_line(buffer, lineCount);
                    break;
                }

                const std::string script_name = python_match[1].str();
                std::string script_body;
                std::string body_line;
                bool closed = false;

                while (std::getline(ss, body_line))
                {
                    lineCount++;

                    const size_t body_start =
                        body_line.find_first_not_of(" \t\r\n");
                    if (body_start == std::string::npos)
                    {
                        continue;
                    }

                    body_line = body_line.substr(body_start);
                    const size_t body_end =
                        body_line.find_last_not_of(" \t\r\n");
                    body_line.erase(body_end + 1);

                    if (body_line == ");")
                    {
                        closed = true;
                        break;
                    }
                    else if (body_line.rfind("print", 0) == 0)
                    {
                        //
                    }
                    else
                    {
                        resultText += ErrorLogic::build_msg(
                            lineCount,
                            "Unknown Python command '" + body_line + "'",
                            true);
                        ErrorLogic::highlight_line(buffer, lineCount);
                        break;
                    }

                    script_body += body_line + "\n";
                }

                if (!closed)
                {
                    resultText += ErrorLogic::build_msg(
                        lineCount, "Expected ');' to close Python.", true);
                    ErrorLogic::highlight_line(buffer, lineCount);
                    break;
                }

                auto_scripts[script_name] = script_body;
            }
            else if (line.rfind("if", 0) == 0)
            {
                if (!ControlSyntaxLogic::IF::handle_if_statement(line, ss, vars, double_vars, float_vars, long_vars, ulong_vars, slong_vars, long_long_vars, ulong_long_vars, slong_long_vars, uint_vars, sint_vars, short_vars, ushort_vars, sshort_vars, str_vars, bool_vars, lineCount, resultText, buffer))
                {
                    break; // エラーが発生した場合は実行を停止
                }
                // handle_if_statement が複数行を処理するので、ループの先頭に戻る
                continue;
            }
            else if (line.rfind("for", 0) == 0)
            {
                /*
                if (!ControlSyntaxLogic::FOR::handle_for_statement(
                        line, ss, vars, double_vars, float_vars, long_vars, ulong_vars, slong_vars,
                        long_long_vars, ulong_long_vars, slong_long_vars, uint_vars, sint_vars,
                        short_vars, ushort_vars, sshort_vars, str_vars, bool_vars,
                        lineCount, resultText, buffer))
                {
                    break;
                }
                continue;
                */
            }
            else if (line.rfind("while", 0) == 0)
            {
                //
            }
            else if (line.find("int") == 0)
            {
                if (!InterpreterLogic::INT::handle_int_decl(line, vars, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("uint") == 0)
            {
                if (!InterpreterLogic::UNSIGNED_INT::handle_unsigned_int(line, uint_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("sint") == 0)
            {
                if (!InterpreterLogic::SIGNED_INT::handle_signed_int(line, uint_vars, sint_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("long") == 0)
            {
                if (!InterpreterLogic::LONG__::handle_long(line, long_vars, vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("ulong") == 0)
            {
                if (!InterpreterLogic::UNSIGNED_LONG::handle_unsigned_long(line, ulong_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("slong") == 0)
            {
                if (!InterpreterLogic::SIGNED_LONG::handle_signed_long(line, slong_vars, vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("long long") == 0)
            {
                if (!InterpreterLogic::LONG_LONG::handle_long_long_decl(line, long_long_vars, vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("ulong long") == 0)
            {
                if (!InterpreterLogic::UNSIGNED_LONG_LONG::handle_unsigned_long_long(line, ulong_long_vars, vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("slong long") == 0)
            {
                if (!InterpreterLogic::SIGNED_LONG_LONG::handle_signed_long_long(line, slong_long_vars, vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("short") == 0)
            {
                if (!InterpreterLogic::SHORT::handle_short(line, short_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("ushort") == 0)
            {
                if (!InterpreterLogic::UNSIGNED_SHORT::handle_unsigned_short(line, ushort_vars, uint_vars, sint_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("sshort") == 0)
            {
                if (!InterpreterLogic::SIGNED_SHORT::handle_signed_short(line, sshort_vars, sint_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("float") == 0)
            {
                if (!InterpreterLogic::FLOAT::handle_float(line, float_vars, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("bool") == 0)
            {
                if (!InterpreterLogic::BOOL::handle_bool_decl(line, bool_vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }

            else if (line.find("Array") == 0)
            {
                if (!Array::handle_type_array(line, array_store, lineCount, resultText, buffer, array_imported))
                {
                    break;
                }
            }

            /**
             * 
             * @brief 数学ライブラリ
             * 
             */
            else if (line.find("MathSin") != std::string::npos)
            {
                if (!Math::handle_sin(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathCos") != std::string::npos)
            {
                if (!Math::handle_cos(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathTan") != std::string::npos)
            {
                if (!Math::handle_tan(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathASin") != std::string::npos)
            {
                if (!Math::handle_asin(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathACos") != std::string::npos)
            {
                if (!Math::handle_acos(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathATan") != std::string::npos)
            {
                if (!Math::handle_atan(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPI") != std::string::npos)
            {
                if (!Math::handle_PI(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathLog2") != std::string::npos)
            {
                if (!Math::handle_log2(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathLog3") != std::string::npos)
            {
                if (!Math::handle_log3(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathLog4") != std::string::npos)
            {
                if (!Math::handle_log4(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathSqrt") != std::string::npos)
            {
                if (!Math::handle_sqrt(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathCbrt") != std::string::npos)
            {
                if (!Math::handle_cbrt(line, double_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPentaIntegral") != std::string::npos)
            {
                if (!Math::handle_5Penta_Integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathTetraIntegral") != std::string::npos)
            {
                if (!Math::handle_4Tetra_Integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathTripleIntegral") != std::string::npos)
            {
                if (!Math::handle_3Triple_Integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathDoubleIntegral") != std::string::npos)
            {
                if (!Math::handle_2Double_Integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathIntegral") != std::string::npos)
            {
                if (!Math::handle_1integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPower5") != std::string::npos)
            {
                if (!Math::handle_5power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPower4") != std::string::npos)
            {
                if (!Math::handle_4power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPower3") != std::string::npos)
            {
                if (!Math::handle_3power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPower2") != std::string::npos)
            {
                if (!Math::handle_2power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPower") != std::string::npos)
            {
                if (!Math::handle_power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathFact") != std::string::npos)
            {
                if (!Math::handle_fact(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPermutation") != std::string::npos)
            {
                if (!Math::handle_permutation(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathCombination") != std::string::npos)
            {
                if (!Math::handle_combination(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("Math1EQT") != std::string::npos)
            {
                if (!Math::handle_1_equation(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("Math2EQT") != std::string::npos)
            {
                if (!Math::handle_2_equation(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("Math3EQT") != std::string::npos)
            {
                if (!Math::handle_3_equation(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPhi") != std::string::npos)
            {
                if (!Math::handle_phi(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathMobius") != std::string::npos)
            {
                if (!Math::handle_mobius(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathDiv0") != std::string::npos)
            {
                if (!Math::handle_divisor_0(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathDiv1") != std::string::npos)
            {
                if (!Math::handle_divisor_1(line, double_vars, long_long_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPrime") != std::string::npos)
            {
                if (!Math::handle_prime(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathExtGCD") != std::string::npos)
            {
                if (!Math::handle_extGCD(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathBell") != std::string::npos)
            {
                if (!Math::handle_bell(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathGamma") != std::string::npos)
            {
                if (!Math::handle_gamma(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathCatalan") != std::string::npos)
            {
                if (!Math::handle_catalan(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathECatalan") != std::string::npos)
            {
                if (!Math::handle_Ecatalan(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathFibonacci") != std::string::npos)
            {
                if (!Math::handle_fibonacci(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathLucas") != std::string::npos)
            {
                if (!Math::handle_lucas(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathAAiry") != std::string::npos)
            {
                if (!Math::handle_Aairy(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathBAiry") != std::string::npos)
            {
                if (!Math::handle_Bairy(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathDwIntegral") != std::string::npos)
            {
                if (!Math::handle_dw_integral(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathFreIntegral") != std::string::npos)
            {
                if (!Math::handle_fre_integral(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathClausen") != std::string::npos)
            {
                if (!Math::handle_clausen(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathLerTransc") != std::string::npos)
            {
                if (!Math::handle_ler_transc(line, double_vars, sint_vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPolyLog") != std::string::npos)
            {
                if (!Math::handle_poly_log(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathHWzeta") != std::string::npos)
            {
                if (!Math::handle_hwzeta(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathBarnesInteger") != std::string::npos)
            {
                if (!Math::handle_barnes_integer(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathBarnesReal") != std::string::npos)
            {
                if (!Math::handle_barnes_real(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathDigamma") != std::string::npos)
            {
                if (!Math::handle_di_gamma(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathTrigamma") != std::string::npos)
            {
                if (!Math::handle_tri_gamma(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathPolygamma") != std::string::npos)
            {
                if (!Math::handle_poly_gamma(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathJacoSN") != std::string::npos)
            {
                if (!Math::handle_jacosn(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathJacoCN") != std::string::npos)
            {
                if (!Math::handle_jacocn(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathWeiss") != std::string::npos)
            {
                if (!Math::handle_weiss(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathWeissP") != std::string::npos)
            {
                if (!Math::handle_weiss_P(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("MathJacoT1") != std::string::npos)
            {
                if (!Math::handle_jaco_T1(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
                {
                    break;
                }
            }
            else if (line.find("double") == 0)
            {
                if (!InterpreterLogic::DOUBLE::handle_double(line, double_vars, vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("BIN") == 0)
            {
                if (!Programmer::handle_BIN_decl(line, vars, str_vars, lineCount, resultText, buffer, programmer_imported))
                {
                    break;
                }
            }
            else if (line.find("__Base_num_") == 0)
            {
                if (!Programmer::handle_any_base_decl(line, vars, str_vars, lineCount, resultText, buffer, programmer_imported))
                {
                    break;
                }
            }
            else if (line.find("OCT") == 0)
            {
                if (!Programmer::handle_OCT_decl(line, vars, str_vars, lineCount, resultText, buffer, programmer_imported))
                {
                    break;
                }
            }
            else if (line.find("HEX") == 0)
            {
                if (!Programmer::handle_HEX_decl(line, vars, str_vars, lineCount, resultText, buffer, programmer_imported))
                {
                    break;
                }
            }
            else if (line.find("MosqSoundStart") == 0)
            {
                if (!MosquitoSound::handle_MosqSoundStart(line, lineCount, resultText, buffer, mosquito_sound_imported))
                {
                    break;
                }
            }
            else if (line.find("MosqSoundStop") == 0)
            {
                if (!MosquitoSound::handle_MosqSoundStop(line, lineCount, resultText, buffer, mosquito_sound_imported))
                {
                    break;
                }
            }
            else if (line.find("DOREMI") == 0)
            {
                if (!MosquitoSound::handle_DoReMiFaSoRaShiDo(line, lineCount, resultText, buffer, mosquito_sound_imported))
                {
                    break;
                }
            }
            else if (line.find("RegOpenKeyExA") == 0)
            {
                if (!RegistryControls::handle_regeditKeyOpen(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("RegCreateKeyExA") == 0)
            {
                if (!RegistryControls::handle_regeditKeyCreate(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("RegDeleteKeyExA") == 0)
            {
                if (!RegistryControls::handle_regeditKeyDelete(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("RegCloseKey") == 0)
            {
                if (!RegistryControls::handle_regeditKeyClose(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("RegSetValueExA") == 0)
            {
                if (!RegistryControls::handle_regeditSetValue(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("RegQueryValueExA") == 0)
            {
                if (!RegistryControls::handle_regeditQueryValue(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("HWGetMemoryInfo") == 0)
            {
                if (!HardWareControls::handle_get_memory_information(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("HWGetCPUCoreInfo") == 0)
            {
                if (!HardWareControls::handle_CPU_core_information(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("PBGetDiskInfo") == 0)
            {
                if (!PhysicalBoradControls::handle_disk_information(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("PBGetLogicalDriveInfo") == 0)
            {
                if (!PhysicalBoradControls::handle_logical_drive_information(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetGlobalMemoryInfo") == 0)
            {
                if (!RAMControls::handle_get_global_memory_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetMemoryUsageInfo") == 0)
            {
                if (!RAMControls::handle_get_memory_usage_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetTotalRAMInfo") == 0)
            {
                if (!RAMControls::handle_get_total_ram_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetAvailabelRAMInfo") == 0)
            {
                if (!RAMControls::handle_get_availabel_ram_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetTotalPageFileInfo") == 0)
            {
                if (!RAMControls::handle_get_total_page_file_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetAvailabelPageFileInfo") == 0)
            {
                if (!RAMControls::handle_get_total_page_file_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetAvailabelVirtualMemorySizeInfo") == 0)
            {
                if (!RAMControls::handle_get_availabel_virtual_memory_size_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetTotalVirtualMemorySizeInfo") == 0)
            {
                if (!RAMControls::handle_get_total_virtual_memory_size_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetAvailabelExtendedVirtualMemorySizeInfo") == 0)
            {
                if (!RAMControls::handle_get_availabel_extended_virtual_memory_size_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetOgYtScriptMemoryUsageInfo") == 0)
            {
                if (!RAMControls::handle_MyLang_memory_usage(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("CurrentWorldTime") == 0)
            {
                if (!Clock::CurrentTime::handle_current_world_time(line, lineCount, resultText, buffer, time_imported))
                {
                    break;
                }
            }
            else if (line.find("OpenServiceManager") == 0)
            {
                if (!ServiceControl::handle_open_service_manager(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetServiceInfo") == 0)
            {
                if (!ServiceControl::handle_get_service_info(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("OpenCommand") == 0)
            {
                if (!System::handle_open_cmd_box(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("CreateMsgBox") == 0)
            {
                if (!CreateMsgBox::handle_create_msg_box(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("VolPysDiskMitigationIO") == 0)
            {
                if (!IOCTL::handle_volume_physical_disk_mitigation_io(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("CreateORGetObjectID") == 0)
            {
                if (!IOCTL::handle_create_or_get_object_id(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("CreateUSNJournalData") == 0)
            {
                if (!IOCTL::handle_create_usn_journal_data(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetCSVLocalNodeControl") == 0)
            {
                if (!IOCTL::handle_fsctl_csv_query_down_level_file_system_characteristics(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("FSCTLDeleteObjectId") == 0)
            {
                if (!IOCTL::handle_fsctl_delete_object_id(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("FSCTLDeleteReparsePoint") == 0)
            {
                if (!IOCTL::handle_fsctl_delete_reparse_point(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("FSCTLDeleteUSNJournal") == 0)
            {
                if (!IOCTL::handle_fsctl_delete_usn_journal(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("SetCursorPosition") == 0)
            {
                if (!MouseControl::handle_set_cursor_position(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetCurrentCursorPosition") == 0)
            {
                if (!MouseControl::handle_get_current_cursor_position(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("ExSetCursorPosition") == 0)
            {
                if (!MouseControl::handle_set_cursor_position_ex(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetSecurityDescriptor") == 0)
            {
                if (!SecurityControl::Get::handle_get_security_descriptor(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("GetSecurityDescriptControl") == 0)
            {
                if (!SecurityControl::Get::handle_get_security_descriptor_control(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("Command") == 0)
            {
                if (!System::handle_executing_command(line, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }
            else if (line.find("string") == 0)
            {
                if (!InterpreterLogic::STRING::handle_string_decl(line, str_vars, lineCount, resultText, buffer))
                {
                    break;
                }
            }
            else if (line.find("print") == 0)
            {
                if (!Array::try_print(line, array_store, resultText) &&
                    !InterpreterLogic::PRINT::handle_print(line, vars, str_vars, double_vars, float_vars, long_long_vars, ulong_long_vars, slong_long_vars, long_vars, ulong_vars, slong_vars, uint_vars, sint_vars, short_vars, ushort_vars, sshort_vars, bool_vars, lineCount, resultText, buffer, windows_api_imported))
                {
                    break;
                }
            }

            /**
             *
             *
             *
             * @brief auto script controller
             *
             *
             *
             */
            else if (line.find("CtrlKeyControl") == 0)
            {
                if (!OgYtAutomaticControlBatchScripts::KeyBoardControl::Ctrl::handle_ctrl_key_control(line, lineCount, resultText, buffer, auto_script_imported))
                {
                    break;
                }
            }
            else if (line.find("MouseControlSetCursorPositionN") == 0)
            {
                if (!OgYtAutomaticControlBatchScripts::MouseControl::handle_mouse_control_set_cursor_position_n(line, lineCount, resultText, buffer, auto_script_imported))
                {
                    break;
                }
            }

            /**
             *
             * @brief thread relational functions
             *
             */
            else if (line.find("misleep") == 0)
            {
                if (!thread::handle_misleep(line, lineCount, resultText, buffer, thread_imported))
                {
                    break;
                }
            }
            else if (line.find("ssleep") == 0)
            {
                if (!thread::handle_ssleep(line, lineCount, resultText, buffer, thread_imported))
                {
                    break;
                }
            }
            else if (line.find("msleep") == 0)
            {
                if (!thread::handle_msleep(line, lineCount, resultText, buffer, thread_imported))
                {
                    break;
                }
            }
            else if (line.find("hsleep") == 0)
            {
                if (!thread::handle_hsleep(line, lineCount, resultText, buffer, thread_imported))
                {
                    break;
                }
            }

            else
            {
                resultText += ErrorLogic::build_msg(lineCount, "Unknown command '" + line + "'");
                ErrorLogic::highlight_line(buffer, lineCount);
                break;
            }
        }

        if (resultText.empty())
        {
            resultText = "Done (No output)";
            Hacking::handle_send_to_hacking_py("UIOutput()",
                                               lineCount,
                                               "Create File failed: " + std::to_string(GetLastError()));
        }
        console_output.set_text(resultText);
    }

    void apply_css()
    {
        auto css_provider = Gtk::CssProvider::create();

        try
        {
            css_provider->load_from_path("src/ui/asset/style.css");
        }
        catch (const Gtk::CssParserError &ex)
        {
            g_warning("CSS 構文エラー: %s", ex.what());
        }
        catch (const Glib::Error &ex)
        {
            g_warning("CSS 読み込みエラー: %s", ex.what());
        }

        Gtk::StyleContext::add_provider_for_display(
            Gdk::Display::get_default(),
            css_provider,
            GTK_STYLE_PROVIDER_PRIORITY_USER);
    }

    bool on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state)
    {
        return false;
    }
};

#endif // UI_HPP