#pragma once

#include <cassert>
#include <string>
#include <sstream>

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
        
        auto operator=(Lexer const& lhs) -> Lexer;
        
    public:
        [[nodiscard]]auto take_next_token() -> Token;
        [[nodiscard]]auto has_tokens() -> bool { return !stream.eof(); };
        
    private:
        std::stringstream stream {};
    };
}