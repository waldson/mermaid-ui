#include "mermaid/components/Cursor.h"

#include <algorithm>
#include <iostream>

mermaid::components::Cursor::Cursor() :
    color(Color(0, 0, 0)), blinkInterval(0.5), elapsedTime(0), up(true), mermaid::components::View()
{
    setSize(3, 10);
}

std::shared_ptr<mermaid::components::Cursor> mermaid::components::Cursor::create()
{
    auto cursor = new mermaid::components::Cursor();
    return std::shared_ptr<mermaid::components::Cursor>(cursor);
}

void mermaid::components::Cursor::update(Context& ctx)
{
    if (blinkInterval > 0) {
        elapsedTime += ctx.deltaTime / 1000;
        if (up) {
            color.a = std::min<int>(255, static_cast<int>(255.0 * (elapsedTime / blinkInterval)));
        } else {
            color.a = std::max<int>(0, 255 - static_cast<int>(255.0 * (elapsedTime / blinkInterval)));
        }
        if (elapsedTime > blinkInterval) {
            while (elapsedTime > blinkInterval) {
                elapsedTime -= blinkInterval;
            }
            up = !up;
        }
    } else {
        color.a = 255;
    }
    setBackground(color);
}
