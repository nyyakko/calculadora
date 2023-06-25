#pragma once

#include "ui/Layout.hpp"

#include <fmt/format.h>
#include <raylib.h>

#include <functional>
#include <string_view>
#include <stack>

#define FNMACRO_BEG do{
#define FNMACRO_END } while(0)

#define DRAW_TEXT(CONTAINER, FONTSIZE, COLOR, FMT, ...)                                                                                            \
        FNMACRO_BEG                                                                                                                                \
            auto const positionX = (CONTAINER.x + (CONTAINER.width / 2)) - MeasureText(message.data(), GetFontDefault().baseSize) - message.size();\
            auto const positionY = (CONTAINER.y + (CONTAINER.height / 2)) - GetFontDefault().baseSize;                                             \
            auto const position  = Vector2 { positionX, positionY };                                                                               \
                                                                                                                                                   \
            DrawText(fmt::format(fmt::runtime(FMT), __VA_ARGS__).data(), position.x, position.y, FONTSIZE, COLOR);                                 \
        FNMACRO_END

namespace ui::gfx
{
    inline auto button(float buttonSpacing, size_t fontSize, Color background, Color foreground, auto&& message)
    {
        auto container = ui::layout_slot();
        container.width -= buttonSpacing;
        container.x += buttonSpacing / 2;
        container.height -= buttonSpacing;
        
        bool clicked = false;
        
        if (CheckCollisionPointRec(GetMousePosition(), container))
        {
            // DrawRectangle(container, ColorBrightness(background, 0.2f));
            DrawRectangleRounded(container, 0.125f, 2, ColorBrightness(background, 0.2f));
            
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // DrawRectangle(container, ColorBrightness(background, 0.01f));
                DrawRectangleRounded(container, 0.125f, 2, ColorBrightness(background, 0.01f));
                clicked = true;
            }
        }
        else
        {
            // DrawRectangle(container, background);
            DrawRectangleRounded(container, 0.125f, 2, background);
        }
        
        DRAW_TEXT(container, fontSize, foreground, message);
        
        return clicked;
    }
}