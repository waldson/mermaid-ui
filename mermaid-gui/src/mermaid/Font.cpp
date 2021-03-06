#include "mermaid/Font.h"

#include "mermaid/Core.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

mermaid::Font::Font(std::string name, unsigned size) : name(name), size(size), font(nullptr)
{
    font = TTF_OpenFont(name.c_str(), size);
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

const std::string& mermaid::Font::getName() const
{
    return name;
}

unsigned mermaid::Font::getSize() const
{
    return size;
}

std::unique_ptr<mermaid::Font> mermaid::Font::create(std::string name, unsigned size)
{
    auto font = new mermaid::Font(name, size);

    return std::unique_ptr<mermaid::Font>(font);
}

mermaid::Size mermaid::Font::getTextSize(std::string text)
{
    mermaid::Size size(0, 0);
    TTF_SizeUTF8(font, text.c_str(), &size.width, &size.height);

    return size;
}

int mermaid::Font::getHeight()
{
    return TTF_FontHeight(font);
}
