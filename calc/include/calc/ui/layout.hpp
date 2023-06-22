#pragma once

#include <raylib.h>

#include <vector>
#include <stack>
#include <cmath>

namespace ui
{
    enum class Orientation
    {
        HORIZONTAL, VERTICAL
    };
    
    struct Layout
    {
        Orientation orientation;
        Rectangle container;
        
        std::vector<Rectangle> items;
    };

    auto layout_begin(Orientation orientation, Rectangle container, size_t count) -> void;
    auto layout_end() -> void;
    auto layout_slot() -> Rectangle;
}