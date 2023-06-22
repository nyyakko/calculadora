#include "calc/lexer.hpp"

#include <stacktrace>
#include <iostream>

using namespace logic;

auto Lexer::operator=(Lexer const& lhs) -> Lexer
{
    if (lhs.stream.str().empty())
    {
        return *this;
    }

    this->stream = std::stringstream { lhs.stream.str() };

    return *this;
}

auto Lexer::take_next_token() -> Token
{
    if (!(this->has_tokens()))
    {
        std::clog << std::stacktrace::current();
        assert(false && "cannot tokenize empty stream");
    }

    Token result {};

    this->stream >> result.value;

    if (std::isdigit(result.value.front()))
    {
        result.type = TokenType::NUMBER;
        result.precedence = TokenPrecedence::NONE;
    }

    if (std::ispunct(result.value.front()))
    {
        result.type = TokenType::OPERATOR;

        switch (result.value.front())
        {
        case '+':
        case '-':
            result.precedence = TokenPrecedence::TERTIARY;
            break;

        case '*':
        case '/':
            result.fixity = TokenFixity::LEFT;
            result.precedence = TokenPrecedence::SECONDARY;
            break;
            
        default:
            assert(false && "invalid token");
        }
    }

    return result;
}