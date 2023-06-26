#include "calc/Calc.hpp"

#include "calc/ui/Color.hpp"
#include "calc/ui/components/Button.hpp"
#include "calc/ui/components/TextBox.hpp"
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

void expression_manipulations(Calc& app)
{
    ui::layout_begin(ui::LayoutOrientation::VERTICAL, ui::layout_slot(), 3);
    {
        if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "POP"sv))
        {
            app.expression_pop();
        }

        if(ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "PUSH"sv))
        {
            app.expression_push();
        }

        if(ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "CLEAR"sv))
        {
            app.expression_clear();
        }
    }
    ui::layout_end();
}

void expression_functions(Calc& app)
{
    ui::layout_begin(ui::LayoutOrientation::VERTICAL, ui::layout_slot(), 3);
    {
        if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "SIN"sv))
        {
            app.expression_append("SIN ");
        }
        
        if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "COS"sv))
        {
            app.expression_append("COS ");
        }
        
        if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "TAN"sv))
        {
            app.expression_append("TAN ");
        }
    }
    ui::layout_end();
    
    ui::layout_begin(ui::LayoutOrientation::VERTICAL, ui::layout_slot(), 3);
    {
        if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "SQRT"sv))
        {
            app.expression_append("SQRT ");
        }
        
        if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "LOG"sv))
        {
            app.expression_append("LOG ");
        }
        
        if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "POW"sv))
        {
            app.expression_append("POW ");
        }
    }
    ui::layout_end();
}

void render(Calc& app)
{
    ClearBackground(ui::color::OBSIDIAN);
    
    ui::layout_begin(ui::LayoutOrientation::VERTICAL, { 0, 0, app.width, app.heigth }, 6);
    {
        ui::gfx::textbox(ui::color::OBSIDIAN, RAYWHITE, FONT_SIZE, app.expression);
        
        ui::layout_begin(ui::LayoutOrientation::HORIZONTAL, ui::layout_slot(), 2);
        {
            if (!app.shiftMode)
            {
                expression_manipulations(app);
                
                if (ui::gfx::button(BUTTON_GAP, FONT_SIZE, ui::color::CHARCOAL, RAYWHITE, "="sv))
                {
                    app.expression_evaluate();
                }
            }
            else
            {
                expression_functions(app);
            }
        }
        ui::layout_end();

        ui::layout_begin(ui::LayoutOrientation::HORIZONTAL, ui::layout_slot(), 4);
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
        
        ui::layout_begin(ui::LayoutOrientation::HORIZONTAL, ui::layout_slot(), 4);
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
        
        ui::layout_begin(ui::LayoutOrientation::HORIZONTAL, ui::layout_slot(), 4);
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
        
        ui::layout_begin(ui::LayoutOrientation::HORIZONTAL, ui::layout_slot(), 4);
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