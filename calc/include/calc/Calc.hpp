#pragma once

#include "calc/Lexer.hpp"

#include <raylib.h>

#include <stack>
#include <sstream>

auto update(class Calc& app) -> void;
auto render(class Calc& app) -> void;

class Calc
{
    using Expression = std::string;
    
public:
    Calc(std::string_view title, size_t width, size_t heigth)
        : width(width), heigth(heigth)
    {
        InitWindow(width, heigth, title.data());
    }

    ~Calc() { CloseWindow(); }

public:
    int run()
    {
        SetTargetFPS(24);
        
        while (!WindowShouldClose())
        {
            BeginDrawing();
                update(*this);
                render(*this);
            EndDrawing();
        }
        
        return 0;
    }
    
    void expression_push()
    {
        this->expressions.push(this->expression);
    }
    
    void expression_pop()
    {
        this->expressions.pop();
    }
    
    void expression_clear()
    {
        this->expression.clear();
    }
    
    void expression_evaluate()
    {
        logic::Lexer lexer { expression };
        std::stringstream stream {};
        stream << logic::evaluate(logic::parse(lexer));
        stream >> this->expression;
    }
    
    void expression_append(std::string_view value)
    {
        this->expression += value;
    }
    
public:
    float width = {}, heigth = {};
    
    Expression expression {};
    std::stack<Expression> expressions {};
};