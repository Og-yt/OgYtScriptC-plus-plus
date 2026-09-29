#ifndef COMPARSIONOPERATOR_HPP
#define COMPARSIONOPERATOR_HPP

#include <gtkmm.h>
#include <string>

namespace FindComparsionOperators
{
    inline bool find_comparsion_operators(const std::string &condition,
                                          std::string &op, // out: 見つかった演算子
                                          size_t &op_pos)  // out: 見つかった演算子の位置
    {
        if ((op_pos = condition.find("==")) != std::string::npos)
        {
            op = "==";
        }
        else if ((op_pos = condition.find("!=")) != std::string::npos)
        {
            op = "!=";
        }
        else if ((op_pos = condition.find("<=")) != std::string::npos)
        {
            op = "<=";
        }
        else if ((op_pos = condition.find(">=")) != std::string::npos)
        {
            op = ">=";
        }
        else if ((op_pos = condition.find("<")) != std::string::npos)
        {
            op = "<";
        }
        else if ((op_pos = condition.find(">")) != std::string::npos)
        {
            op = ">";
        }
        else
        {
            return false;
        }
        return true;
    }
}

#endif // COMPARSIONOPERATOR_HPP