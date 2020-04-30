#ifndef MERMAID_FONT_H
#define MERMAID_FONT_H

#include "mermaid/Core.h"

#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>

namespace mermaid {

class Font
{

  public:
    static std::unique_ptr<mermaid::Font> create(std::string name, unsigned size);
    ~Font();
    const std::string& getName() const;
    unsigned getSize() const;
    TTF_Font* asSdlPointer();
    operator TTF_Font*() const;
    mermaid::Size getTextSize(std::string text);

  private:
    std::string name;
    unsigned size;
    TTF_Font* font;
    Font(std::string name, unsigned size);
};
} // namespace mermaid
#endif
