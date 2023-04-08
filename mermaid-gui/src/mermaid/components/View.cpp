#include "mermaid/components/View.h"

#include "mermaid/Core.h"
#include "mermaid/SdlContext.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/Component.h"

#include <SDL2_gfxPrimitives.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <algorithm>
#include <iostream>
#include <memory>

using namespace mermaid;

mermaid::components::View::View(int x, int y, int width, int height) : mermaid::components::Widget(), m_borderRadius(0)
{
    setPosition(x, y);
    setSize(width, height);
}

mermaid::components::View::View() : mermaid::components::View(0, 0, 0, 0)
{
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

    // SDL_SetRenderTarget(renderer, texture);
    const auto rect = getDrawRect();
    auto& drawContext = ctx.window->getRenderer().getDrawContext();
    drawContext.push().setRGBA255(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

    if (m_borderRadius > 0) {
        drawContext.drawRoundedRectangle(rect.x, rect.y, rect.width, rect.height, m_borderRadius);
    } else {
        drawContext.drawRectangle(rect.x, rect.y, rect.width, rect.height);
    }

    drawContext.fill().pop();

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

void mermaid::components::View::setBorderRadius(float borderRadius)
{
    m_borderRadius = borderRadius;
}
