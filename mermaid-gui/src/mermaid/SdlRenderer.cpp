#include "mermaid/SdlRenderer.h"

#include "cairo.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/graphics/SDL2DrawContext.hpp"

#include <SDL2/SDL.h>
#include <memory>

using namespace mermaid;

mermaid::SdlRenderer::SdlRenderer(SdlWindow* window, int driver_index, unsigned int options) :
    m_window{window}, m_windowWidth{0}, m_windowHeight{0}, m_rendererWidth{0}, m_rendererHeight{}
{
    renderer = SDL_CreateRenderer(window->asSdlPointer(), driver_index, options);
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    initCairo();
}

void mermaid::SdlRenderer::initCairo()
{
    static int i = 0;
    ++i;
    destroyTexturesAndSurfaces();

    SDL_GetWindowSize(m_window->asSdlPointer(), &m_windowWidth, &m_windowHeight);
    SDL_GetRendererOutputSize(renderer, &m_rendererWidth, &m_rendererHeight);

    int cairoXMultiplier = m_rendererWidth / m_windowWidth;
    int cairoYMultiplier = m_rendererHeight / m_windowHeight;

    m_drawSurface =
        SDL_CreateRGBSurface(0, m_rendererWidth, m_rendererHeight, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    m_cairoSurface =
        cairo_image_surface_create_for_data(static_cast<unsigned char*>(m_drawSurface->pixels), CAIRO_FORMAT_RGB24,
                                            m_drawSurface->w, m_drawSurface->h, m_drawSurface->pitch);

    cairo_surface_set_device_scale(m_cairoSurface, cairoXMultiplier, cairoYMultiplier);
    m_cairoContext = cairo_create(m_cairoSurface);

    m_drawTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_rendererWidth,
                                      m_rendererHeight);

    m_drawContext = std::make_unique<graphics::SDL2DrawContext>(m_cairoContext, renderer);
    m_renderRect = SDL_Rect{0, 0, m_rendererWidth, m_rendererHeight};
}

void mermaid::SdlRenderer::onWindowResize(mermaid::Event&)
{
    auto newWidth = 0;
    auto newHeight = 0;

    SDL_GetWindowSize(m_window->asSdlPointer(), &newWidth, &newHeight);
    if (newWidth != m_windowWidth || newHeight != m_windowHeight) {
        initCairo();
    }
}

void mermaid::SdlRenderer::destroyTexturesAndSurfaces()
{
    if (m_cairoContext != nullptr) {
        cairo_destroy(m_cairoContext);
        m_cairoContext = nullptr;
    }

    if (m_cairoSurface != nullptr) {
        cairo_surface_destroy(m_cairoSurface);
        m_cairoSurface = nullptr;
    }

    if (m_drawSurface != nullptr) {
        SDL_FreeSurface(m_drawSurface);
        m_drawSurface = nullptr;
    }

    if (m_drawTexture != nullptr) {
        SDL_DestroyTexture(m_drawTexture);
        m_drawTexture = nullptr;
    }

    m_drawContext.reset(nullptr);
}

mermaid::SdlRenderer::~SdlRenderer()
{
    destroyTexturesAndSurfaces();
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

graphics::DrawContext& mermaid::SdlRenderer::getDrawContext() const
{
    return *m_drawContext.get();
}

void mermaid::SdlRenderer::render()
{
    SDL_UpdateTexture(m_drawTexture, &m_renderRect, m_drawSurface->pixels, m_drawSurface->pitch);
    SDL_RenderCopy(renderer, m_drawTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void mermaid::SdlRenderer::clear()
{
    getDrawContext().push().setRGB(0, 0, 0).drawRectangle(0, 0, m_rendererWidth, m_rendererHeight).fill().pop();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

std::unique_ptr<mermaid::SdlRenderer> mermaid::SdlRenderer::create(SdlWindow* window, int driver_index,
                                                                   unsigned int options)
{
    // TODO: use make_unique
    mermaid::SdlRenderer* renderer = new mermaid::SdlRenderer(window, driver_index, options);

    return std::unique_ptr<mermaid::SdlRenderer>(renderer);
}
