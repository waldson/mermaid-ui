#include "mermaid/components/View.h"

#include "mermaid/Core.h"
#include "mermaid/SdlContext.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/Component.h"

#include <memory>

using namespace mermaid;

mermaid::components::View::View(int x, int y, int width, int height) : mermaid::components::Widget(), components()
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
}

Rect mermaid::components::View::getDrawRect()
{
    auto position = getPosition();
    auto size = getSize();
    Rect rect(position.x, position.y, size.width, size.height);
    return rect;
}

void mermaid::components::View::update(Context& ctx)
{
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
