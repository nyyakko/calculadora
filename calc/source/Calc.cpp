#include "calc/Calc.hpp"

#include "calc/ui/Color.hpp"
#include "calc/ui/gfx/Component.hpp"
#include "calc/ui/gfx/Shape.hpp"
#include "calc/ui/Layout.hpp"

using namespace std::literals;

auto static constexpr FONT_SIZE  = 24;
auto static constexpr BUTTON_GAP = 4;

void update(Calc& app)
{
    if (IsKeyPressed(KEY_LEFT_SHIFT) && !app.shiftMode)
    {
        app.shiftMode = true;
    }
    else
    {
        if (IsKeyPressed(KEY_LEFT_SHIFT) && app.shiftMode)
        {
            app.shiftMode = false;
        }
    }
}

void render(Calc& app)
{
    ClearBackground(ui::color::OBSIDIAN);
    
    ui::layout_begin(ui::Orientation::VERTICAL, { 0, 0, app.width, app.heigth }, 6);
    {
        ui::gfx::textbox(ui::color::OBSIDIAN, RAYWHITE, FONT_SIZE, app.expression);
        
        ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 2);
        {
            ui::layout_begin(ui::Orientation::VERTICAL, ui::layout_slot(), 3);
            {
                if (!app.shiftMode && ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "POP"sv))
                {
                    app.expression_pop();
                }
                else
                {
                    if (app.shiftMode && ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "SIN"sv))
                    {
                        app.expression_append("SIN ");
                    }
                }
                
                if(!app.shiftMode && ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "PUSH"sv))
                {
                    app.expression_push();
                }
                else
                {
                    if (app.shiftMode && ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "COS"sv))
                    {
                        app.expression_append("COS ");
                    }
                }
                
                if(!app.shiftMode && ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "CLEAR"sv))
                {
                    app.expression_clear();
                }
                else
                {
                    if (app.shiftMode && ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "TAN"sv))
                    {
                        app.expression_append("TAN ");
                    }
                }
            }
            ui::layout_end();
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "="sv))
            {
                app.expression_evaluate();
            }
        }
        ui::layout_end();

        ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 4);
        {
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "1"sv))
            {
                app.expression_append("1");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "2"sv))
            {
                app.expression_append("2");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "3"sv))
            {
                app.expression_append("3");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "*"sv))
            {
                app.expression_append(" * ");
            }
        }
        ui::layout_end();
        
        ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 4);
        {
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "4"sv))
            {
                app.expression_append("4");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "5"sv))
            {
                app.expression_append("5");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "6"sv))
            {
                app.expression_append("6");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "/"sv))
            {
                app.expression_append(" / ");
            }
        }
        ui::layout_end();
        
        ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 4);
        {
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "7"sv))
            {
                app.expression_append("7");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "8"sv))
            {
                app.expression_append("8");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "9"sv))
            {
                app.expression_append("9");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "+"sv))
            {
                app.expression_append(" + ");
            }
        }
        ui::layout_end();
        
        ui::layout_begin(ui::Orientation::HORIZONTAL, ui::layout_slot(), 4);
        {
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "0"sv))
            {
                app.expression_append("0");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "("sv))
            {
                app.expression_append("( ");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, ")"sv))
            {
                app.expression_append(" )");
            }
            
            if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "-"sv))
            {
                app.expression_append(" - ");
            }
        }
        ui::layout_end();
    }
    ui::layout_end();
}