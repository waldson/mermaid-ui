#include "mermaid/SdlContext.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_opengl.h>
#include <iostream>
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

    auto window = SdlWindow::create(title, x, y, width, height, options);

    return std::move(window);
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

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    initialized = true;
}
