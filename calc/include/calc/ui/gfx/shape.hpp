#pragma once

#include "ui/Layout.hpp"

#include <raylib.h>
//
namespace ui::gfx
{
    inline auto rectangle(Rectangle container, Color color)
    {
        DrawRectangle(container.x, container.y, container.width, container.height, color);
    }
}