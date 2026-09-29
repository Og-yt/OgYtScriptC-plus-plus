#ifndef RESOLVEKEYCODE_HPP
#define RESOLVEKEYCODE_HPP

#include <windows.h>
#include <map>

inline WORD resolve_key_code(const std::string &key_name)
{
    if (key_name.size() == 1)
    {
        const unsigned char key = static_cast<unsigned char>(key_name.front());
        if (std::isalnum(key))
        {
            return static_cast<WORD>(std::toupper(key));
        }
    }

    static const std::map<std::string, WORD> named_keys = {
        {"ENTER", VK_RETURN},
        {"ESC", VK_ESCAPE},
        {"ESCAPE", VK_ESCAPE},
        {"TAB", VK_TAB},
        {"SPACE", VK_SPACE},
        {"BACKSPACE", VK_BACK},
        {"DELETE", VK_DELETE},
        {"UP", VK_UP},
        {"DOWN", VK_DOWN},
        {"LEFT", VK_LEFT},
        {"RIGHT", VK_RIGHT},
    };

    const auto key = named_keys.find(key_name);
    if (key != named_keys.end())
    {
        return key->second;
    }

    std::size_t parsed_characters = 0;
    const unsigned long numeric_key = std::stoul(key_name, &parsed_characters, 0);
    if (parsed_characters == key_name.size() && numeric_key <= 0xFF)
    {
        return static_cast<WORD>(numeric_key);
    }

    throw std::invalid_argument("unsupported key: " + key_name);
}

#endif // RESOLVEKEYCODE_HPP