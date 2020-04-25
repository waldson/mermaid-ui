#include "mermaid/SdlWindow.h"
#include "mermaid/SdlRenderer.h"

#include <SDL.h>
#include <iostream>
#include <memory>
#include <string_view>

using namespace mermaid;

mermaid::SdlWindow::SdlWindow(std::string_view title, int x, int y, int width, int height, unsigned int options)

    : mermaid::SdlWindow::SdlWindow(title, x, y, width, height, options,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
{
}

mermaid::SdlWindow::SdlWindow(std::string_view title, int x, int y, int width, int height, unsigned int options,
                              unsigned int renderer_options)
{
    sdl_window = SDL_CreateWindow(title.data(), x, y, width, height, options);
    renderer = SdlRenderer::create(this, -1, renderer_options);
}

SDL_Renderer* mermaid::SdlWindow::getRenderer()
{
    return *this->renderer;
}

std::unique_ptr<mermaid::SdlWindow> mermaid::SdlWindow::create(std::string_view title, int x, int y, int width,
                                                               int height, unsigned int options)
{
    // TODO: use make_unique
    mermaid::SdlWindow* window = new mermaid::SdlWindow(title, x, y, width, height, options);

    return std::unique_ptr<mermaid::SdlWindow>(window);
}

mermaid::SdlWindow::operator SDL_Window*() const
{
    return sdl_window;
}

SDL_Window* mermaid::SdlWindow::asSdlPointer() const
{
    return sdl_window;
}

mermaid::SdlWindow::~SdlWindow()
{
    SDL_DestroyWindow(sdl_window);
}
