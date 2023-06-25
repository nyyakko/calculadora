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
    inline auto textbox(Color background, Color foreground, size_t fontSize, auto&& message, auto&&... arguments)
    {
        auto container = ui::layout_slot();
        
        DrawRectangle(container.x, container.y, container.width, container.height, background);
        
        DRAW_TEXT(container, fontSize, foreground, message, arguments...);
    }
}