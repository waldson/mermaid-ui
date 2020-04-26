#include "mermaid/components/Label.h"

#include "mermaid/Application.h"
#include "mermaid/Core.h"
#include "mermaid/helpers/string_helper.h"

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include<iostream>

mermaid::components::Label::Label(std::u8string text, mermaid::Font& font) :
    text(text), font(font), color(0, 0, 0), dirty(true), textureCache(nullptr)
{
}

mermaid::components::Label::~Label()
{
    if (textureCache) {
        SDL_DestroyTexture(textureCache);
        textureCache = nullptr;
    }
}

std::shared_ptr<mermaid::components::Label> mermaid::components::Label::create(std::u8string text, mermaid::Font& font)
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

void mermaid::components::Label::updateSize()
{
    auto str = mermaid::helpers::from_u8string(text);
    TTF_SizeUTF8(font.asSdlPointer(), str.c_str(), &rect.width, &rect.height);
}

mermaid::Rect mermaid::components::Label::getDrawRect()
{
    rect.x = getPosition().x;
    rect.y = getPosition().y;

    if (dirty) {
        updateSize();
    }

    mermaid::Rect parentRect(0, 0, 0, 0);
    if (hasParent()) {
        parentRect = getParent().value()->getDrawRect();
    }

    return mermaid::Rect(parentRect.x + rect.x, parentRect.y + rect.y, rect.width, rect.height);
}

void mermaid::components::Label::draw(Context& ctx)
{
    if (textureCache) {
        auto rect = getDrawRect().toSdlRect();
        SDL_RenderCopy(ctx.window->getRenderer(), textureCache, nullptr, &rect);
    }
}

void mermaid::components::Label::setColor(Color color)
{
    this->color = color;
    dirty = true;
}

void mermaid::components::Label::setText(std::u8string text)
{
    this->text = text;
    dirty = true;
}

void mermaid::components::Label::setFont(Font& font)
{
    this->font = font;
    dirty = true;
}

std::u8string mermaid::components::Label::getText()
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

    auto str = mermaid::helpers::from_u8string(text);

    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(
        TTF_RenderUTF8_Blended(font, str.c_str(), color.toSdlColor()), SDL_FreeSurface);

    SDL_SetSurfaceBlendMode(&*surface, SDL_BLENDMODE_BLEND);
    textureCache = SDL_CreateTextureFromSurface(ctx.window->getRenderer(), &*surface);
    dirty = false;
    /* font.asSdlPointer()->c */
}
