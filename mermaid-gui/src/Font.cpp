#include "mermaid/Font.h"

#include "mermaid/Core.h"
#include "mermaid/helpers/string_helper.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>

mermaid::Font::Font(std::u8string name, unsigned size) : name(name), size(size), font(nullptr)
{
    std::string str = mermaid::helpers::from_u8string(name);

    font = TTF_OpenFont(str.c_str(), size);
    /* TTF_SetFontKerning(font, 1); */
}

mermaid::Font::~Font()
{
    TTF_CloseFont(font);
}

TTF_Font* mermaid::Font::asSdlPointer()
{
    return font;
}

mermaid::Font::operator TTF_Font*() const
{
    return font;
}

const std::u8string& mermaid::Font::getName() const
{
    return name;
}

unsigned mermaid::Font::getSize() const
{
    return size;
}

std::unique_ptr<mermaid::Font> mermaid::Font::create(std::u8string name, unsigned size)
{
    auto font = new mermaid::Font(name, size);

    return std::unique_ptr<mermaid::Font>(font);
}

mermaid::Size mermaid::Font::getTextSize(std::u8string text)
{
    mermaid::Size size(0, 0);
    auto str = mermaid::helpers::from_u8string(text);

    TTF_SizeUTF8(font, str.c_str(), &size.width, &size.height);

    return size;
}
