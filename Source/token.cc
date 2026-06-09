#pragma once
#include <cstdlib>
#include <string>

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
    Token(TokenType newTokenType, string newLexeme, string newLiteral, int newLine)
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

        return string(TokenNames[type]) + " " + lexeme + " " + literal;
    }

    TokenType type;
    string lexeme;
    string literal;
    int line;
};