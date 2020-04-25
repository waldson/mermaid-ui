#include "mermaid/Application.h"
#include "mermaid/Core.h"
#include "mermaid/SdlContext.h"
#include "mermaid/components/View.h"

#include <SDL.h>
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char* argv[])
{
    using namespace mermaid;
    using namespace mermaid::components;

    auto a = SdlContext::create();
    auto window =
        a->createWindow("Teste", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    Application app(*window);
    auto view = View::create(10, 10, 150, 120);
    view->setBackground(50, 60, 90);
    app.setRootComponent(std::move(view));
    app.run();

    return 0;
}
