#ifndef OSTRINGSTREAMTOSTRING_HPP
#define OSTRINGSTREAMTOSTRING_HPP

#include <sstream>
#include <string>

const std::string OstringStreamToString(const std::ostringstream& stream)
{
    return stream.str();
}

#endif // OSTRINGSTREAMTOSTRING_HPP