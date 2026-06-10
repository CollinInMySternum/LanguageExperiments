#pragma once
#include <cstdlib>

enum class LiteralType
{
    NONE,
    INT,
    FLOAT,
    BOOL
};

struct LiteralValue
{
    LiteralType type = LiteralType::NONE;

    union
    {
        long asInt;
        double asFloat;
        bool asBool;
    };

    // Constructors for safety
    LiteralValue() : type(LiteralType::NONE), asInt(0) {}
    LiteralValue(long v) : type(LiteralType::INT), asInt(v) {}
    LiteralValue(double v) : type(LiteralType::FLOAT), asFloat(v) {}
    LiteralValue(bool v) : type(LiteralType::BOOL), asBool(v) {}
};