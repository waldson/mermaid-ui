#include "mermaid/components/View.h"

#include "mermaid/Core.h"
#include "mermaid/SdlContext.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/Component.h"

#include <algorithm>
#include <memory>

using namespace mermaid;

mermaid::components::View::View(int x, int y, int width, int height) : mermaid::components::Widget()
{
    getPosition().x = x;
    getPosition().y = x;
    getSize().width = width;
    getSize().height = height;
}

std::shared_ptr<mermaid::components::View> mermaid::components::View::create(int width, int height)
{
    return mermaid::components::View::create(0, 0, width, height);
}

std::shared_ptr<mermaid::components::View> mermaid::components::View::create(int x, int y, int width, int height)
{
    auto view = new mermaid::components::View(x, y, width, height);
    return std::shared_ptr<components::View>(view);
}

std::shared_ptr<mermaid::components::View> mermaid::components::View::create()
{
    return create(0, 0, 0, 0);
}

void mermaid::components::View::draw(Context& ctx)
{
    if (!isVisible()) {
        return;
    }
    SDL_SetRenderDrawColor(ctx.window->getRenderer(), backgroundColor.r, backgroundColor.g, backgroundColor.b,
                           backgroundColor.a);
    auto rect = getDrawRect().toSdlRect();
    SDL_RenderFillRect(ctx.window->getRenderer(), &rect);
    mermaid::components::Widget::draw(ctx);
}

void mermaid::components::View::setBackground(Color color)
{
    backgroundColor = color;
}

void mermaid::components::View::setBackground(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
    backgroundColor = Color(r, g, b, a);
}

void mermaid::components::View::setBackground(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    backgroundColor = Color(r, g, b);
}

void mermaid::components::View::handleEvent(mermaid::Event& event, mermaid::Context& ctx)
{
    if (event.isMouseMotionEvent()) {
        auto evt = event.getRawEvent();
        mermaid::Point p(evt.motion.x, evt.motion.y);
        auto rect = getDrawRect();
        if (rect.contains(p)) {
            setBackground(Color(150, 50, 50));
        }
        else {
            setBackground(Color(50, 150, 50));
        }
    }
}
