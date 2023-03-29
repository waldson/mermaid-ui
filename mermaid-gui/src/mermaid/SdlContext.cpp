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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    glEnable(GL_MULTISAMPLE);

    options |= SDL_WINDOW_OPENGL;

    auto window = SdlWindow::create(title, x, y, width, height, options);

    int buffers = 0;
    int samples = 0;

    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &buffers);
    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &samples);

    std::cout << "Buffers: " << buffers << ", Samples: " << samples << std::endl;

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

    initialized = true;
}
