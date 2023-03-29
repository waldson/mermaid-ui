#include "mermaid/components/View.h"

#include "mermaid/Core.h"
#include "mermaid/SdlContext.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/Component.h"

#include <SDL2_gfxPrimitives.h>
#include <SDL_pixels.h>
#include <algorithm>
#include <memory>

using namespace mermaid;

int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void draw_circle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

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
    auto* renderer = ctx.window->getRenderer();

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    auto rect = getDrawRect().toSdlRect();

    SDL_RenderFillRect(renderer, &rect);

    // SDL_SetRenderDrawColor(renderer, 255.0f, 255.0f, 255.0f, 255.0f);

    // aacircleRGBA(renderer, 400, 100, 16, 255, 255, 255, 255);
    // filledCircleRGBA(renderer, 400, 100, 16, 255, 255, 255, 255);
    // draw_circle(renderer, 200, 200, 20, SDL_Color(255, 255, 0, 255));
    // SDL_RenderDrawCircle(renderer, 100, 300, 20);
    // SDL_RenderFillCircle(renderer, 100, 300, 20);
    // roundedRectangleRGBA(renderer, 100, 400, 300, 500, 10, 255, 255, 255, 255);
    // roundedBoxRGBA(renderer, 100, 400, 300, 500, 20, 255, 255, 255, 255);

    // SDL_Render
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
