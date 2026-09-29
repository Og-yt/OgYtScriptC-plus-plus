#ifndef FORSTRUCTURE_HPP
#define FORSTRUCTURE_HPP

typedef const char *FVAR, *FSTR;
typedef std::string FCVAR, FCVAL, FLVAR, INITIALVAL;

enum class ForOperator
{
    Less,
    LessEqual,
    Greater,
    GreaterEqual
};

enum class ForIncrement
{
    Increment,
    Decrement
};

struct ForCondition
{
    FCVAR variable;
    ForOperator op;
    FCVAL value;
};

struct ForLoop
{
    FLVAR variable;
    INITIALVAL initialValue;

    ForCondition condition;
    ForIncrement increment;

    int blockDepth;
};

#endif // FORSTRUCTURE_HPP