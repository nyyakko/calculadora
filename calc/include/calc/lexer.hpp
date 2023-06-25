#pragma once

#include <cassert>
#include <string>
#include <sstream>
#include <vector>

namespace logic
{
    enum class TokenType { NUMBER, OPERATOR };
    enum class TokenPrecedence { NONE, TERTIARY, SECONDARY, PRIMARY };
    enum class TokenFixity { LEFT, RIGHT };

    struct Token
    {
        TokenType type;
        TokenPrecedence precedence;
        TokenFixity fixity;
        
        std::string value;
    };

    struct Lexer
    {
        explicit Lexer(std::string const& expression)
            : stream { expression }
        {}
            
        Lexer(Lexer const& lhs)
            : stream { lhs.stream.str() }
        {}
        
        Lexer operator=(Lexer const& lhs);
        
    public:
        [[nodiscard]]Token take_next_token();
        [[nodiscard]]bool has_tokens() { return !stream.eof(); };
        
    private:
        std::stringstream stream {};
    };
    
    std::vector<Token> parse(Lexer lexer);
    float evaluate(std::vector<Token> const& tokens);
}