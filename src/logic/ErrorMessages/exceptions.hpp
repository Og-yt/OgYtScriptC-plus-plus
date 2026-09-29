#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class RuntimeException : public std::exception
{
private:
    std::string message;

public:
    RuntimeException(const std::string &msg) : message(msg) {}
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

class StringIndexOutOfBoundsException : public std::exception
{
private:
    //

public:
    //

protected:
    //
};

#endif // EXCEPTIONS_HPP