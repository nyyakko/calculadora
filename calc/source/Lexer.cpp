#include "calc/Lexer.hpp"

#include <algorithm>
#include <iostream>
#include <stack>
#include <stacktrace>
#include <unordered_map>

static auto operations = std::unordered_map
{
    std::pair { '+', + [] (float lhs, float rhs) { return lhs + rhs; } },
    std::pair { '-', + [] (float lhs, float rhs) { return lhs - rhs; } },
    std::pair { '*', + [] (float lhs, float rhs) { return lhs * rhs; } },
    std::pair { '/', + [] (float lhs, float rhs) { return lhs / rhs; } },
};

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
    
    auto fnIsDigit = [] (auto value) { return std::isdigit(value); };
    
    if (std::ranges::find_if(result.value, fnIsDigit) != std::end(result.value))
    {
        result.type = TokenType::NUMBER;
        result.precedence = TokenPrecedence::NONE;
    }

    if (result.value.size() == 1 && std::ispunct(result.value.front()))
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
                
            case ',':
                result.type = TokenType::COMMA;
                break;
                
            case '(':
                result.type = TokenType::LEFT_PARENTHESIS;
                result.precedence = TokenPrecedence::PRIMARY;
                break;
            case ')':
                result.type = TokenType::RIGHT_PARENTHESIS;
                result.precedence = TokenPrecedence::PRIMARY;
                break;
                
            default:
                assert(false && "invalid token");
        }
    }
    
    if (result.value == "SIN"  || result.value == "COS" || result.value == "TAN" ||
        result.value == "SQRT" || result.value == "LOG" || result.value == "POW")
    {
        result.type = TokenType::FUNCTION;
        result.precedence = TokenPrecedence::NONE;
    }

    return result;
}

auto logic::parse(Lexer lexer) -> std::vector<Token>
{
    std::vector<Token> expression {};
    std::stack<Token> operators {};
    
    while (lexer.has_tokens())
    {
        auto currentToken = lexer.take_next_token();
        
        if (currentToken.type == TokenType::NUMBER)
        {
            expression.push_back(currentToken);
        }
        
        if (currentToken.type == TokenType::FUNCTION)
        {
            operators.push(currentToken);
        }
        
        if (currentToken.type == TokenType::OPERATOR)
        {
            while (!operators.empty())
            {
                auto isTopParenthesis   = operators.top().type == TokenType::LEFT_PARENTHESIS;
                auto hasLowerPrecedence = currentToken.precedence < operators.top().precedence;
                auto hasEqualPrecedence = currentToken.precedence == operators.top().precedence;
                
                if (isTopParenthesis || !(hasLowerPrecedence || (hasEqualPrecedence && currentToken.fixity == TokenFixity::LEFT)))
                {
                    break;
                }
                
                auto lastOperator = operators.top();
                operators.pop();
                
                expression.emplace_back(std::move(lastOperator));
            }
            
            operators.push(currentToken);
        }
        
        if (currentToken.type == TokenType::COMMA)
        {
            while (!operators.empty() && operators.top().type != TokenType::LEFT_PARENTHESIS)
            {
                auto lastOperator = operators.top();
                operators.pop();
                
                expression.emplace_back(std::move(lastOperator));
            }
        }
        
        if (currentToken.type == TokenType::LEFT_PARENTHESIS)
        {
            operators.push(currentToken);
        }
        
        if (currentToken.type == TokenType::RIGHT_PARENTHESIS)
        {
            while (!operators.empty() && operators.top().type != TokenType::LEFT_PARENTHESIS)
            {
                assert(!operators.empty() && "mismatching parenthesis!");
                
                auto lastOperator = operators.top();
                operators.pop();
                
                expression.emplace_back(std::move(lastOperator));
            }
            
            assert((!operators.empty() && operators.top().type == TokenType::LEFT_PARENTHESIS) && "mismatching parenthesis!");
            operators.pop();
            
            if (!operators.empty() && operators.top().type == TokenType::FUNCTION)
            {
                auto lastOperator = operators.top();
                operators.pop();
                
                expression.emplace_back(std::move(lastOperator));
            }
        }
    }
    
    std::ranges::for_each(std::ranges::iota_view { 0zu, operators.size() }, [&](auto)
    {
        assert(operators.top().type != TokenType::LEFT_PARENTHESIS && "mismatching parenthesis!");
        expression.push_back(operators.top());
        operators.pop();
    });
    
    return expression;
}

auto logic::evaluate(std::vector<Token> const& tokens) -> float
{
    std::stack<float> stack {};
    
    for (auto const& token : tokens)
    {
        if (token.type == TokenType::NUMBER)
        {
            float value {};
            std::stringstream { token.value } >> value;

            stack.push(value);
        }
        
        if (token.type == TokenType::OPERATOR)
        {
            auto rhs = stack.top();
            stack.pop();
            auto lhs = stack.top();
            stack.pop();

            stack.push(operations[token.value.front()](lhs, rhs));
        }
        
        if (token.type == TokenType::FUNCTION)
        {
            auto lhs = stack.top();
            stack.pop();
            
            if (token.value == "SIN")
            {
                stack.push(std::sin(lhs));
            }
            
            if (token.value == "COS")
            {
                stack.push(std::cos(lhs));
            }
            
            if (token.value == "TAN")
            {
                stack.push(std::tan(lhs));
            }
            
            if (token.value == "SQRT")
            {
                stack.push(std::sqrt(lhs));
            }
            
            if (token.value == "POW")
            {
                auto rhs = stack.top();
                stack.pop();
                
                stack.push(std::pow(lhs, rhs));
            }
        }
    }

    return stack.top();
}