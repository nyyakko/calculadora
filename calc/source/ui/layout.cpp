#include "calc/ui/layout.hpp"

#include <format>
#include <iostream>
#include <cassert>
#include <stacktrace>

static inline auto& layout_stack()
{
    static std::stack<ui::Layout> stack {};
    return stack;
}

auto ui::layout_begin(Orientation orientation, Rectangle container, size_t count) -> void
{
    Layout layout
    {
        .orientation = orientation,
        .container = container,
        .items = {}
    };
    
    layout.items.reserve(count);
    
    layout_stack().push(std::move(layout));
}

auto ui::layout_end() -> void
{
    layout_stack().pop();
}

auto ui::layout_slot() -> Rectangle
{
    if (!(layout_stack().top().items.size() < layout_stack().top().items.capacity()))
    {
        std::clog << std::stacktrace::current();
        assert(false && "cannot push to stack, would overflow");
    }
    
    Rectangle rectangle;
    
    auto const& root = layout_stack().top();
    auto const& container = root.container;
    
    switch (root.orientation)
    {
        case Orientation::HORIZONTAL:
            rectangle.width  = std::ceilf(container.width / root.items.capacity());
            rectangle.height = container.height;
            rectangle.x      = container.x + std::ceilf((container.width / root.items.capacity()) * root.items.size());
            rectangle.y      = container.y;
            
            break;
        
        case Orientation::VERTICAL:
            rectangle.width  = container.width;
            rectangle.height = std::ceilf(container.height / root.items.capacity());
            rectangle.x      = container.x;
            rectangle.y      = container.y + std::ceilf((container.height / root.items.capacity()) * root.items.size());
            
            break;
    }
    
    layout_stack().top().items.push_back(rectangle);
    
    return rectangle;
}