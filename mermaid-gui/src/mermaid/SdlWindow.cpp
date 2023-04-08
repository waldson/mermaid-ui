#include "mermaid/SdlWindow.h"

#include "mermaid/SdlRenderer.h"

#include <SDL2/SDL.h>
#include <memory>
#include <string>

using namespace mermaid;

mermaid::SdlWindow::SdlWindow(std::string title, int x, int y, int width, int height, unsigned int options)

    :
    mermaid::SdlWindow::SdlWindow(title, x, y, width, height, options,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
{
}

mermaid::SdlWindow::SdlWindow(std::string title, int x, int y, int width, int height, unsigned int options,
                              unsigned int renderer_options)
{
    sdl_window = SDL_CreateWindow(title.c_str(), x, y, width, height, options);
    renderer = SdlRenderer::create(this, -1, renderer_options);
}

mermaid::SdlRenderer& mermaid::SdlWindow::getRenderer()
{
    return *this->renderer;
}

std::unique_ptr<mermaid::SdlWindow> mermaid::SdlWindow::create(std::string title, int x, int y, int width, int height,
                                                               unsigned int options)
{
    mermaid::SdlWindow* window = new mermaid::SdlWindow(title, x, y, width, height, options);

    return std::unique_ptr<mermaid::SdlWindow>(window);
}

mermaid::SdlWindow::operator SDL_Window*() const
{
    return sdl_window;
}

int mermaid::SdlWindow::getWidth() const
{
    int w = 0;
    int h = 0;

    SDL_GetWindowSizeInPixels(sdl_window, &w, &h);

    return w;
}

int mermaid::SdlWindow::getHeight() const
{
    int w = 0;
    int h = 0;

    SDL_GetWindowSizeInPixels(sdl_window, &w, &h);

    return h;
}

SDL_Window* mermaid::SdlWindow::asSdlPointer() const
{
    return sdl_window;
}

mermaid::SdlWindow::~SdlWindow()
{
    SDL_DestroyWindow(sdl_window);
}
