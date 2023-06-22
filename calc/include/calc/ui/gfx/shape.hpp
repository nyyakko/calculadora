#pragma once

#include "calc/ui/layout.hpp"

#include <raylib.h>

namespace ui::gfx
{
    inline auto rectangle(auto&& container, auto&& color) -> void
    {
        DrawRectangle(container.x, container.y, container.width, container.height, color);
    }
}