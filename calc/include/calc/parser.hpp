#pragma once

#include "calc/lexer.hpp"

#include <vector>

namespace logic
{
    auto parse(Lexer lexer) -> std::vector<Token>;
    auto evaluate(std::vector<Token> const& tokens) -> float;
}