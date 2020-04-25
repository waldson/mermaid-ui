#ifndef MERMAID_SDLWINDOW_H
#define MERMAID_SDLWINDOW_H
#include <SDL.h>
#include <memory>
#include <mermaid/SdlRenderer.h>
#include <string_view>

namespace mermaid {

class SdlWindow
{
  public:
    static std::unique_ptr<mermaid::SdlWindow> create(std::string_view title, int x, int y, int width, int height,
                                                      unsigned int options);
    ~SdlWindow();

    SDL_Renderer* getRenderer();

    operator SDL_Window*() const;
    SDL_Window* asSdlPointer() const;

  private:
    SdlWindow(std::string_view title, int x, int y, int width, int height, unsigned int options);

    SdlWindow(std::string_view title, int x, int y, int width, int height, unsigned int options,
              unsigned int renderer_options);

    SDL_Window* sdl_window;
    std::unique_ptr<SdlRenderer> renderer;
};
} // namespace mermaid
#endif
