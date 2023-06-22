#include "calc/parser.hpp"

#include <algorithm>
#include <stack>
#include <unordered_map>

auto operations = std::unordered_map
{
    std::pair { '+', + [] (float lhs, float rhs) { return lhs + rhs; } },
    std::pair { '-', + [] (float lhs, float rhs) { return lhs - rhs; } },
    std::pair { '*', + [] (float lhs, float rhs) { return lhs * rhs; } },
    std::pair { '/', + [] (float lhs, float rhs) { return lhs / rhs; } },
};

auto logic::parse(Lexer lexer) -> std::vector<Token>
{
    auto localLexer = lexer;
    
    std::vector<Token> tokens {};
    std::stack<Token> operators {};
    
    while (lexer.has_tokens())
    {
        auto currentToken = lexer.take_next_token();
        
        if (currentToken.type == TokenType::NUMBER)
        {
            tokens.push_back(currentToken);
        }
        
        if (currentToken.type == TokenType::OPERATOR)
        {
            while (!operators.empty())
            {
                auto hasLowerPrecedence = currentToken.precedence < operators.top().precedence;
                auto hasEqualPrecedence = currentToken.precedence == operators.top().precedence;
                
                if (!(hasLowerPrecedence || (hasEqualPrecedence && currentToken.fixity == TokenFixity::LEFT)))
                {
                    break;
                }
                
                auto lastOperator = operators.top();
                operators.pop();
                
                tokens.emplace_back(std::move(lastOperator));
            }
            
            operators.push(currentToken);
        }
    }
    
    std::ranges::for_each(std::ranges::iota_view { 0zu, operators.size() }, [&](auto)
    {
        tokens.push_back(operators.top());
        operators.pop();
    });
    
    return tokens;
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
    }

    return stack.top();
}