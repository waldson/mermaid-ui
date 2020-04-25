#include "mermaid/components/View.h"
#include "mermaid/Context.h"
#include "mermaid/Core.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/Component.h"

#include <memory>

using namespace mermaid;

mermaid::components::View::View(int x, int y, int width, int height)
{
    options.set("position", Point(x, y));
    options.set("size", Size(width, height));
    options.set("backgroundColor", Color());
    options.set("margin", Margin());
    options.set("padding", Padding());
    options.set("border", Border());
}

std::unique_ptr<mermaid::components::View> mermaid::components::View::create(int width, int height)
{
    return mermaid::components::View::create(0, 0, width, height);
}

std::unique_ptr<mermaid::components::View> mermaid::components::View::create(int x, int y, int width, int height)
{
    auto view = new mermaid::components::View(x, y, width, height);
    return std::unique_ptr<components::View>(view);
}

std::unique_ptr<mermaid::components::View> mermaid::components::View::create()
{
    return create(0, 0, 0, 0);
}

void mermaid::components::View::draw(Context ctx)
{
    auto bg = options.get<Color>("backgroundColor").value();
    auto position = options.get<Point>("position").value();
    auto size = options.get<Size>("size").value();

    SDL_SetRenderDrawColor(ctx.window->getRenderer(), bg.r, bg.g, bg.b, bg.a);
    SDL_Rect rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.w = size.width;
    rect.h = size.height;

    SDL_RenderFillRect(ctx.window->getRenderer(), &rect);
}

void mermaid::components::View::update(Context ctx)
{
}

void mermaid::components::View::setBackground(Color color)
{
    options.set("backgroundColor", color);
}

void mermaid::components::View::setBackground(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
    options.set("backgroundColor", Color(r, g, b, a));
}

void mermaid::components::View::setBackground(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    options.set("backgroundColor", Color(r, g, b));
}
