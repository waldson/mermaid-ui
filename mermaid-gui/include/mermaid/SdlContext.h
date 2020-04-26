#ifndef W5N_SDLCONTEXT_H
#define W5N_SDLCONTEXT_H

#include "mermaid/SdlWindow.h"

#include <SDL2/SDL.h>
#include <memory>

namespace mermaid {

class SdlContext
{
  public:
    static std::unique_ptr<mermaid::SdlContext> create();
    void init();

    std::unique_ptr<mermaid::SdlWindow> createWindow(std::u8string title, int x, int y, int width, int height,
                                                     unsigned int options);
    ~SdlContext();

  private:
    SdlContext();

    bool initialized;
};
} // namespace mermaid

#endif
