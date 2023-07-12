#ifndef MERMAID_SDLWINDOW_H
#define MERMAID_SDLWINDOW_H

#include "mermaid/SdlRenderer.h"

#include <SDL2/SDL.h>
#include <memory>
#include <string>

namespace mermaid {

class SdlWindow
{
  public:
    static std::unique_ptr<mermaid::SdlWindow> create(std::string title, int x, int y, int width, int height,
                                                      unsigned int options);
    ~SdlWindow();

    SdlRenderer& getRenderer();

    operator SDL_Window*() const;
    SDL_Window* asSdlPointer() const;

    int getWidth() const;
    int getHeight() const;

  private:
    SdlWindow(std::string title, int x, int y, int width, int height, unsigned int options);

    SdlWindow(std::string title, int x, int y, int width, int height, unsigned int options,
              unsigned int renderer_options);

    SDL_Window* sdl_window;
    std::unique_ptr<SdlRenderer> renderer;
};
} // namespace mermaid
#endif
