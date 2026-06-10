#pragma once

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "token.cc"

using namespace std;

class Scanner
{
public:
    Scanner(string newSource)
    {
        source = newSource;
    }

    bool IsAtEnd()
    {
        return current >= source.length();
    }

    char Advance()
    {
        return source[current++];
    }

    char Peek()
    {
        if (IsAtEnd())
            return '\0';

        return source[current];
    }

    char PeekNext()
    {
        if (current + 1 >= source.length())
            return '\0';

        return source[current + 1];
    }

    bool NextMatch(char expectedChar)
    {
        if (IsAtEnd())
            return false;
        if (source[current] != expectedChar)
            return false;

        current++;
        return true;
    }

    bool IsDigit(char c)
    {
        return c >= '0' && c <= '9';
    }

    bool IsAlpha(char c)
    {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               c == '_';
    }

    bool IsAlphaNumeric(char c)
    {
        return IsAlpha(c) || IsDigit(c);
    }

    void TokenizeNumber()
    {
        bool isFloat = false;

        while (IsDigit(Peek()))
            Advance();

        if (Peek() == '.' && IsDigit(PeekNext()))
        {
            isFloat = true;
            Advance();

            while (IsDigit(Peek()))
                Advance();
        }

        std::string numberStr = source.substr(start, current - start);

        if (isFloat)
        {
            AddToken(NUMBER, LiteralValue(std::stod(numberStr)));
        }
        else
        {
            AddToken(NUMBER, LiteralValue(std::stol(numberStr)));
        }
    }

    void TokenizeIdentifier()
    {
        while (IsAlphaNumeric(Peek()))
            Advance();

        AddToken(IDENTIFIER);
    }

    void ScanToken()
    {
        char c = Advance();

        switch (c)
        {
        case '(':
            AddToken(LEFT_PAREN);
            break;
        case ')':
            AddToken(RIGHT_PAREN);
            break;
        case '{':
            AddToken(LEFT_BRACE);
            break;
        case '}':
            AddToken(RIGHT_BRACE);
            break;
        case ',':
            AddToken(COMMA);
            break;
        case '.':
            AddToken(DOT);
            break;
        case ';':
            AddToken(SEMICOLON);
            break;
        case '-':
            AddToken(MINUS);
            break;
        case '+':
            AddToken(PLUS);
            break;
        case '*':
            AddToken(STAR);
            break;

        case '!':
            AddToken(NextMatch('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            AddToken(NextMatch('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            AddToken(NextMatch('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            AddToken(NextMatch('=') ? GREATER_EQUAL : GREATER);
            break;

        case '/':
            if (NextMatch('/'))
            {
                // Skip comments
                while (Peek() != '\n' && !IsAtEnd())
                    Advance();
            }
            else
            {
                AddToken(SLASH);
            }
            break;

        case '&':
            if (NextMatch('&'))
            {
                AddToken(AND);
            }
            else
            {
                error(line, "Unexpected character.");
            }
            break;

        case '|':
            if (NextMatch('|'))
            {
                AddToken(OR);
            }
            else
            {
                error(line, "Unexpected character.");
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;

        case '\n':
            line++;
            break;

        default:
            if (IsDigit(c))
            {
                TokenizeNumber();
            }
            else if (IsAlpha(c))
            {
                TokenizeIdentifier();
            }
            else
            {
                error(line, "Unexpected character.");
            }
            break;
        }
    }

    void ScanTokens()
    {
        while (!IsAtEnd())
        {
            start = current;
            ScanToken();
        }

        tokens.push_back(Token(END, "", "", line));
    }

    void AddToken(TokenType type)
    {
        AddToken(type, LiteralValue());
    }

    void AddToken(TokenType type, LiteralValue literal)
    {
        string text = source.substr(start, current - start);
        tokens.push_back(Token(type, text, literal, line));
    }

    int start = 0;
    int current = 0;
    int line = 0;

    string source;
    vector<Token> tokens;
    // ERROR HANDLING
public:
    void error(int line, string message)
    {
        report(line, "", message);
    }

private:
    void report(int line, string where, string message)
    {
        cout << "[line " << line << "] Error" << where << ": " << message << "\n";
        hasError = true;
    }

    bool hasError = false;
};