#pragma once

#include <raylib.h>

#include <vector>
#include <stack>
#include <cmath>
//
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

    void layout_begin(Orientation orientation, Rectangle container, size_t count);
    void layout_end();
    Rectangle layout_slot();
}