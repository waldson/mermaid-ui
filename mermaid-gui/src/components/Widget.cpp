#include "mermaid/components/Widget.h"

#include <iostream>

mermaid::components::Widget::Widget() :
    size(0, 0), position(0, 0), padding(), margin(), border(), options(), visible(true)
{
}

mermaid::Size& mermaid::components::Widget::getSize()
{
    return size;
}

void mermaid::components::Widget::setSize(int width, int height)
{
    size.width = width;
    size.height = height;
}

void mermaid::components::Widget::setSize(mermaid::Size size)
{
    this->size = size;
}

void mermaid::components::Widget::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void mermaid::components::Widget::setPosition(mermaid::Point p)
{
    position = p;
}

mermaid::Point& mermaid::components::Widget::getPosition()
{
    return position;
}

mermaid::Padding& mermaid::components::Widget::getPadding()
{
    return padding;
}

mermaid::Margin& mermaid::components::Widget::getMargin()
{
    return margin;
}

mermaid::Border& mermaid::components::Widget::getBorder()
{
    return border;
}

bool mermaid::components::Widget::hasOption(std::u8string key)
{
    return options.has(key);
}

void mermaid::components::Widget::unsetOption(std::u8string key)
{
    options.unset(key);
}

mermaid::Options& mermaid::components::Widget::getOptions()
{
    return options;
}
