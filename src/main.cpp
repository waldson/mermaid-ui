#include "mermaid/Application.h"
#include "mermaid/Core.h"
#include "mermaid/Font.h"
#include "mermaid/SdlContext.h"
#include "mermaid/components/Label.h"
#include "mermaid/components/View.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char* argv[])
{
    using namespace mermaid;
    using namespace mermaid::components;

    auto a = SdlContext::create();
    auto window =
        a->createWindow(u8"Teste", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    Application app(*window);
    auto view = View::create(20, 20, 760, 50);

    auto font = Font::create(u8"/home/waldson/.local/share/fonts/Hack Regular Nerd Font Complete.ttf", 18);
    const std::u8string label = u8"Hoje é dia de fazer compras";
    auto text = Label::create(label, *font);

    view->setBackground(50, 60, 70);
    text->setColor(Color(150, 200, 200));
    text->setSize(100, 100);
    text->setPosition(30, 33);
    view->addChild(text);

    app.setRootComponent(view);

    /* app.setRootComponent(std::move(view)); */
    app.run();

    return 0;
}
