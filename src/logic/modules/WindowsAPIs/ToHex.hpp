#ifndef TOHEX_HPP
#define TOHEX_HPP

#include <sstream>
#include <iomanip>
#include <string>

#define PARAGRAPH (code == 0 ? "\n" : (code == 2) ? "\n\n" : " ")

typedef std::string STREAM;

/**
 *
 * @brief 値を受け取って 0xNN 形式に変換する名前空間関数
 *
 */
namespace To_16
{
    inline STREAM handle_to_hex_int(int value, int code)
    {
        std::ostringstream oss;

        oss << std::hex << value << std::dec << (code == 0 ? "\n" : "");

        return oss.str();
    }

    /**
     * 
     * @brief 第2引数が 0 の場合改行をする, 2 の場合2回改行 それ以外: 空白
     * 
     */
    inline STREAM handle_to_hex_ushort(unsigned short value, int code)
    {
        std::ostringstream oss;

        oss << std::hex << value << std::dec << PARAGRAPH;

        return oss.str();
    }

    namespace X2
    {
        inline STREAM handle_to_hex_int(int value)
        {
            std::ostringstream oss;

            oss << "0x"
                << std::hex
                << std::uppercase
                << std::setfill('0')
                << std::setw(2)
                << value;

            return oss.str();
        }

        inline STREAM handle_to_hex_uint(unsigned int value)
        {
            std::ostringstream oss;

            oss << "0x"
                << std::hex
                << std::uppercase
                << std::setfill('0')
                << std::setw(2)
                << value;

            return oss.str();
        }

        inline STREAM handle_to_hex_ulong(unsigned long value)
        {
            std::ostringstream oss;

            oss << "0x"
                << std::hex
                << std::uppercase
                << std::setfill('0')
                << std::setw(2)
                << value;

            return oss.str();
        }

        inline STREAM handle_to_hex_uchar(unsigned char value)
        {
            std::ostringstream oss;

            oss << "0x"
                << std::hex
                << std::uppercase
                << std::setfill('0')
                << std::setw(2)
                << value;

            return oss.str();
        }
    }

    namespace X8
    {
        inline STREAM handle_to_hex_uint(unsigned int value)
        {
            std::ostringstream oss;

            oss << "0x"
                << std::hex
                << std::uppercase
                << std::setfill('0')
                << std::setw(8)
                << value;

            return oss.str();
        }

        inline STREAM handle_to_hex_ulong(unsigned long value)
        {
            std::ostringstream oss;

            oss << "0x"
                << std::hex
                << std::uppercase
                << std::setfill('0')
                << std::setw(8)
                << value;

            return oss.str();
        }
    }
}

#endif // TOHEX_HPP