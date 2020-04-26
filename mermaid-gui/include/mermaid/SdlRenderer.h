#ifndef MERMAID_SDLRENDERER_H
#define MERMAID_SDLRENDERER_H
#include <SDL2/SDL.h>
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
    ~SdlRenderer();

  private:
    SdlRenderer(SdlWindow* window, int driver_index, unsigned int options);
    SDL_Renderer* renderer;
};
} // namespace mermaid
#endif
