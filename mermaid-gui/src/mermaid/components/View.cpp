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

mermaid::components::View::View(int x, int y, int width, int height) : mermaid::components::Widget()
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
    drawContext.push()
        .setRGBA255(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a)
        .drawRectangle(rect.x, rect.y, rect.width, rect.height)
        .fill()
        .pop();

    // SDL_RenderFillRect(renderer, &rect);
    //
    // SDL_SetRenderDrawColor(renderer, 255.0f, 255.0f, 0.0f, 255.0f);

    // aacircleRGBA(renderer, 400, 100, 16, 255, 255, 255, 255);
    // filledCircleRGBA(renderer, 400, 100, 16, 255, 255, 255, 255);
    // draw_circle(renderer, 200, 200, 20, SDL_Color(255, 255, 0, 255));
    // SDL_RenderDrawCircle(renderer, 100, 300, 20);
    // SDL_RenderFillCircle(renderer, 100, 300, 20);
    // SDL_RenderDrawCircle(renderer, 200, 200, 48);
    // roundedRectangleRGBA(renderer, 100, 400, 300, 500, 10, 255, 255, 255, 255);

    // aacircleColor(renderer, 100, 300, 20, 16776960);
    // filledCircleRGBA(renderer, 100, 400, 10, 255, 255, 0, 255);
    // aaellipseRGBA(renderer, 100, 300, 20, 20, 255, 255, 0, 255);

    // SDL_RenderFillCircle(renderer, 100, 300, 10);
    // aaFilledEllipseRGBA(renderer, 100, 300, 20, 20, 255, 255, 0, 255);
    // roundedBoxRGBA(renderer, 10, 10, 100, 100, 10, 255, 255, 0, 255);
    // roundedBoxRGBA(renderer, 100, 400, 300, 500, 20, 255, 255, 255, 255);

    // SDL_Render
    mermaid::components::Widget::draw(ctx);
    // const SDL_Rect wRect{0, 0, width, height};
    // SDL_RenderCopy(renderer, texture, &wRect, &wRect);

    // SDL_SetRenderTarget(renderer, nullptr);
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
