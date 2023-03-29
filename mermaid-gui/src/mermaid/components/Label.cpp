#include "mermaid/components/Label.h"

#include "mermaid/Application.h"
#include "mermaid/Core.h"

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

mermaid::components::Label::Label(std::string text, mermaid::Font& font) :
    text(text), font(font), color(0, 0, 0), dirty(true), textureCache(nullptr)
{
    updateSize();
}

mermaid::components::Label::~Label()
{
    if (textureCache) {
        SDL_DestroyTexture(textureCache);
        textureCache = nullptr;
    }
}

std::shared_ptr<mermaid::components::Label> mermaid::components::Label::create(std::string text, mermaid::Font& font)
{
    auto label = new mermaid::components::Label(text, font);

    return std::shared_ptr<mermaid::components::Label>(label);
}

void mermaid::components::Label::update(Context& ctx)
{
    mermaid::components::Widget::update(ctx);
    if (dirty) {
        updateSize();
        updateTexture(ctx);
        dirty = false;
    }
}
mermaid::Size mermaid::components::Label::calculateSize(const std::string& value) const
{
    mermaid::Size size;
    TTF_SizeUTF8(font.asSdlPointer(), value.c_str(), &size.width, &size.height);

    return size;
}

void mermaid::components::Label::updateSize()
{
    mermaid::Size size;
    TTF_SizeUTF8(font.asSdlPointer(), text.c_str(), &size.width, &size.height);
    setSize(size);
}

void mermaid::components::Label::draw(Context& ctx)
{
    if (textureCache) {
        auto rect = getDrawRect().toSdlRect();

        SDL_RenderCopy(ctx.window->getRenderer(), textureCache, nullptr, &rect);
    } else {
        dirty = true;
    }
}

void mermaid::components::Label::setColor(Color color)
{
    this->color = color;
    dirty = true;
}

mermaid::Color mermaid::components::Label::getColor()
{
    return color;
}

void mermaid::components::Label::setText(std::string text)
{
    this->text = text;
    dirty = true;
}

void mermaid::components::Label::setFont(Font& font)
{
    this->font = font;
    dirty = true;
}

mermaid::Font& mermaid::components::Label::getFont()
{
    return font;
}

std::string mermaid::components::Label::getText()
{
    return text;
}

void mermaid::components::Label::setParent(std::shared_ptr<Widget> parent)
{
    mermaid::components::Widget::setParent(parent);
    dirty = true;
}

void mermaid::components::Label::updateTexture(Context& ctx)
{
    if (textureCache) {
        SDL_DestroyTexture(textureCache);
        textureCache = nullptr;
    }

    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(
        TTF_RenderUTF8_Blended(font, text.c_str(), color.toSdlColor()), SDL_FreeSurface);

    SDL_SetSurfaceBlendMode(&(*surface), SDL_BLENDMODE_BLEND);
    textureCache = SDL_CreateTextureFromSurface(ctx.window->getRenderer(), &(*surface));
    dirty = false;
    /* font.asSdlPointer()->c */
}
