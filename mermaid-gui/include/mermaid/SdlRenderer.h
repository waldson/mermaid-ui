#ifndef MERMAID_SDLRENDERER_H
#define MERMAID_SDLRENDERER_H

#include "mermaid/Event.h"
#include "mermaid/graphics/DrawContext.hpp"

#include <SDL2/SDL.h>
#include <cairo.h>
#include <memory>

namespace mermaid {

class SdlWindow;

class SdlRenderer
{
  public:
    static std::unique_ptr<mermaid::SdlRenderer> create(SdlWindow* window, int driver_index = -1,
                                                        unsigned int options = SDL_RENDERER_ACCELERATED |
                                                                               SDL_RENDERER_PRESENTVSYNC);
    operator SDL_Renderer*() const;
    SDL_Renderer* asSdlPointer() const;
    graphics::DrawContext& getDrawContext() const;
    void onWindowResize(mermaid::Event& event);
    void render();
    void clear();
    ~SdlRenderer();

  private:
    SdlRenderer(SdlWindow* window, int driver_index, unsigned int options);
    void initCairo();
    void destroyTexturesAndSurfaces();
    SdlWindow* m_window;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* m_drawSurface = nullptr;
    SDL_Texture* m_drawTexture = nullptr;
    SDL_Rect m_renderRect;
    cairo_surface_t* m_cairoSurface = nullptr;
    cairo_t* m_cairoContext = nullptr;
    std::unique_ptr<graphics::DrawContext> m_drawContext;

    int m_windowWidth;
    int m_windowHeight;
    int m_rendererWidth;
    int m_rendererHeight;
};
} // namespace mermaid
#endif
