#pragma once
#include <cstdlib>
#include <string>
#include "literals.cc"

enum TokenType
{
    COMMA,     // ,
    DOT,       // .
    SEMICOLON, // ;

    MINUS, // -
    PLUS,  // +
    SLASH, // /
    STAR,  // *

    LEFT_PAREN,  // (
    RIGHT_PAREN, // )
    LEFT_BRACE,  // {
    RIGHT_BRACE, // }

    BANG,       // !
    BANG_EQUAL, // !=

    EQUAL,       // =
    EQUAL_EQUAL, // ==

    GREATER,       // >
    GREATER_EQUAL, // >=

    LESS,       // <
    LESS_EQUAL, // <=

    IDENTIFIER,
    NUMBER,

    AND, // &&
    OR,  // ||

    IF,   // if
    ELSE, // else

    TRUE,  // true
    FALSE, // false

    END
};

using namespace std;

class Token
{
public:
    Token(TokenType newTokenType, string newLexeme, LiteralValue newLiteral, int newLine)
    {
        type = newTokenType;
        lexeme = newLexeme;
        literal = newLiteral;
        line = newLine;
    }

    string ToString()
    {
        const char *TokenNames[] = {
            "COMMA", "DOT", "SEMICOLON", "MINUS", "PLUS", "SLASH", "STAR",
            "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
            "BANG", "BANG_EQUAL", "EQUAL", "EQUAL_EQUAL",
            "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL",
            "IDENTIFIER", "NUMBER", "AND", "OR", "IF", "ELSE", "TRUE", "FALSE", "END"};

        std::string literalStr = "";

        switch (literal.type)
        {
        case LiteralType::INT:
            literalStr = std::to_string(literal.asInt);
            break;
        case LiteralType::FLOAT:
            literalStr = std::to_string(literal.asFloat);
            break;
        case LiteralType::BOOL:
            literalStr = literal.asBool ? "true" : "false";
            break;
        case LiteralType::NONE:
            literalStr = "null";
            break;
        }

        return string(TokenNames[type]) + " " + lexeme + " " + literalStr;
    }

    TokenType type;
    string lexeme;
    LiteralValue literal;
    int line;
};