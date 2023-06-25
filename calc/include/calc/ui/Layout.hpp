#pragma once

#include <raylib.h>

#include <vector>
#include <stack>
#include <cmath>

namespace ui
{
    enum class LayoutOrientation
    {
        HORIZONTAL, VERTICAL
    };
    
    struct Layout
    {
        LayoutOrientation orientation;
        Rectangle container;
        
        std::vector<Rectangle> items;
    };

    void layout_begin(LayoutOrientation orientation, Rectangle container, size_t count);
    void layout_end();
    Rectangle layout_slot();
}