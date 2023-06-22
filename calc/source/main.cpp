#include "calc/lexer.hpp"
#include "calc/parser.hpp"
#include "calc/ui/gfx/component.hpp"
#include "calc/ui/gfx/shape.hpp"
#include "calc/ui/layout.hpp"

#include <fmt/format.h>
#include <raylib.h>

#include <algorithm>
#include <iostream>
#include <stack>

auto static constexpr FACTOR   = 40;
auto static constexpr WIDTH    = 9 * FACTOR;
auto static constexpr HEIGHT   = 16 * FACTOR;
auto static constexpr OBSIDIAN = Color { 31, 31, 31, 255 };
auto static constexpr CHARCOAL = Color { 24, 24, 24, 255 };

auto main() -> int
{
    InitWindow(WIDTH, HEIGHT, "calc");
    
    SetTargetFPS(60);
    
    using namespace std::literals;
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(OBSIDIAN);
        
        ui::layout_begin(ui::Orientation::VERTICAL, { 0, 0, WIDTH, HEIGHT }, 6);
            
            static std::string prompt {};
            static std::stack<std::string> expressions {};
            
            ui::gfx::label(ui::layout_slot(), OBSIDIAN, RAYWHITE, 24, prompt);
            
            ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 2);
                ui::layout_begin(ui::Orientation::VERTICAL, ui::layout_slot(), 3);
                    ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "POP"sv, [] (auto&&)
                    {
                        if (expressions.empty())
                        {
                            return;
                        }

                        prompt = expressions.top();
                        expressions.pop();
                    });
                    
                    ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "PUSH"sv, [] (auto&&)
                    {
                        expressions.push(prompt);
                    });
                    
                    ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "CLEAR"sv, [] (auto&&)
                    {
                        prompt.clear();
                    });
                ui::layout_end();
                
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "="sv, [] ([[maybe_unused]]auto&& value)
                {
                    logic::Lexer lexer { prompt };
                    prompt = std::to_string(logic::evaluate(logic::parse(lexer)));
                });
            ui::layout_end();
            
            auto fnPushToken = [] (auto&& value)
            {
                if (!std::isdigit(value.front()))
                {
                    prompt += " ";
                    prompt += value;
                    prompt += " ";
                }
                else
                {
                    prompt += value;
                }
            };
            
            ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 4);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "1"sv, fnPushToken);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "2"sv, fnPushToken);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "3"sv, fnPushToken);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "*"sv, fnPushToken);
            ui::layout_end();
            ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 4);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "4"sv, fnPushToken);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "5"sv, fnPushToken);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "6"sv, fnPushToken);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "/"sv, fnPushToken);
            ui::layout_end();
            ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 4);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "7"sv, fnPushToken);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "8"sv, fnPushToken);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "9"sv, fnPushToken);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "+"sv, fnPushToken);
            ui::layout_end();
            ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 4);
                ui::gfx::rectangle(ui::layout_slot(), OBSIDIAN);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "0"sv, fnPushToken);
                ui::gfx::rectangle(ui::layout_slot(), OBSIDIAN);
                ui::gfx::button(ui::layout_slot(), CHARCOAL, RAYWHITE, 24, "-"sv, fnPushToken);
            ui::layout_end();
        ui::layout_end();

        EndDrawing();
    }
}