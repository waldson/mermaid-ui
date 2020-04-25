#include "mermaid/SdlRenderer.h"
#include "mermaid/SdlWindow.h"

#include <SDL.h>

using namespace mermaid;

mermaid::SdlRenderer::SdlRenderer(SdlWindow* window, int driver_index, unsigned int options)
{
    renderer = SDL_CreateRenderer(window->asSdlPointer(), driver_index, options);
}

mermaid::SdlRenderer::~SdlRenderer()
{
    SDL_DestroyRenderer(renderer);
}

mermaid::SdlRenderer::operator SDL_Renderer*() const
{
    return renderer;
}

SDL_Renderer* mermaid::SdlRenderer::asSdlPointer() const
{
    return renderer;
}

std::unique_ptr<mermaid::SdlRenderer> mermaid::SdlRenderer::create(SdlWindow* window, int driver_index,
                                                                   unsigned int options)
{
    // TODO: use make_unique
    mermaid::SdlRenderer* renderer = new mermaid::SdlRenderer(window, driver_index, options);

    return std::unique_ptr<mermaid::SdlRenderer>(renderer);
}
