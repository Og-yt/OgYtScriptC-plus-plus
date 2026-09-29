#ifndef ARRAY_STORE_HPP
#define ARRAY_STORE_HPP

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace ArrayVariables
{
    using Value = std::variant<
        std::vector<int>,
        std::vector<double>,
        std::vector<long long>,
        std::vector<std::string>>;

    struct Variable
    {
        std::string type;
        Value values;
    };

    struct Store
    {
        std::map<std::string, Variable> variables;
    };
}

#endif // ARRAY_STORE_HPP
