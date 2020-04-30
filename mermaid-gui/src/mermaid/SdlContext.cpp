#include "mermaid/SdlContext.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <string_view>

using namespace mermaid;

mermaid::SdlContext::SdlContext() : initialized(false)
{
}

mermaid::SdlContext::~SdlContext()
{
    if (initialized) {
        TTF_Quit();
        SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
        SDL_Quit();
    }
}

std::unique_ptr<SdlWindow> mermaid::SdlContext::createWindow(std::string title, int x, int y, int width, int height,
                                                             unsigned int options)
{
    this->init();
    return SdlWindow::create(title, x, y, width, height, options);
}

std::unique_ptr<mermaid::SdlContext> mermaid::SdlContext::create()
{
    auto context = new SdlContext();
    return std::unique_ptr<mermaid::SdlContext>(context);
}

void mermaid::SdlContext::init()
{
    if (initialized) {
        return;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error("Error initializing SDL.");
    }

    if (TTF_Init() != 0) {
        throw std::runtime_error("Error initializing TTF fonts.");
    }

    initialized = true;
}
