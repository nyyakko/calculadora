#pragma once

#include "calc/ui/gfx/shape.hpp"

#include <fmt/format.h>
#include <raylib.h>

#include <functional>
#include <string_view>

#define FNMACRO_BEG do{
#define FNMACRO_END } while(0)

#define DRAW_TEXT(COLOR, FONTSIZE, POSX, POSY, FMT, ...)                                               \
        FNMACRO_BEG                                                                                    \
            DrawText(fmt::format(fmt::runtime(FMT), __VA_ARGS__).data(), POSX, POSY, FONTSIZE, COLOR); \
        FNMACRO_END

namespace ui::gfx
{
    inline auto label(Rectangle container, Color background, Color foreground, size_t size, auto&& message, auto&&... arguments)
    {
        rectangle(container, background);
        
        auto const positionX = (container.x + (container.width / 2)) - MeasureText(message.data(), GetFontDefault().baseSize) - message.size();
        auto const positionY = (container.y + (container.height / 2)) - GetFontDefault().baseSize;
        
        DRAW_TEXT(foreground, size, positionX, positionY, message, arguments...);
    }
    
    inline auto button(Rectangle container, Color background, Color foreground, size_t size, auto&& message, auto&& functor)
    {
        bool clicked = false;
        
        container.width -= 4;
        container.x += 2;
        container.height -= 4;
        
        if (CheckCollisionPointRec(GetMousePosition(), container))
        {
            // rectangle(container, ColorBrightness(background, 0.2f));
            DrawRectangleRounded(container, 0.125f, 2, ColorBrightness(background, 0.2f));
            
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                functor(message);
                // rectangle(container, ColorBrightness(background, 0.01f));
                DrawRectangleRounded(container, 0.125f, 2, ColorBrightness(background, 0.01f));
                clicked = true;
            }
        }
        else
        {
            // rectangle(container, background);
            DrawRectangleRounded(container, 0.125f, 2, background);
        }
        
        auto const positionX = (container.x + (container.width / 2)) - MeasureText(message.data(), GetFontDefault().baseSize) - message.size();
        auto const positionY = (container.y + (container.height / 2)) - GetFontDefault().baseSize;
        
        DRAW_TEXT(foreground, size, positionX, positionY, message);
        
        return clicked;
    }
    
    inline auto button(Rectangle container, Color background, Color foreground, size_t size, auto&& message)
    {
        return button(container, background, foreground, size, message, [] (auto) {});
    }
}