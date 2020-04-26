#include "mermaid/SdlWindow.h"

#include "mermaid/SdlRenderer.h"
#include "mermaid/helpers/string_helper.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>

using namespace mermaid;

mermaid::SdlWindow::SdlWindow(std::u8string title, int x, int y, int width, int height, unsigned int options)

    :
    mermaid::SdlWindow::SdlWindow(title, x, y, width, height, options,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
{
}

mermaid::SdlWindow::SdlWindow(std::u8string title, int x, int y, int width, int height, unsigned int options,
                              unsigned int renderer_options)
{
    sdl_window = SDL_CreateWindow(mermaid::helpers::from_u8string(title).c_str(), x, y, width, height, options);
    renderer = SdlRenderer::create(this, -1, renderer_options);
}

SDL_Renderer* mermaid::SdlWindow::getRenderer()
{
    return *this->renderer;
}

std::unique_ptr<mermaid::SdlWindow> mermaid::SdlWindow::create(std::u8string title, int x, int y, int width, int height,
                                                               unsigned int options)
{
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
