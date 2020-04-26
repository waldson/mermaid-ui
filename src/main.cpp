#include "mermaid/Application.h"
#include "mermaid/Core.h"
#include "mermaid/Font.h"
#include "mermaid/ResourceManager.h"
#include "mermaid/components/HBox.h"
#include "mermaid/components/Label.h"
#include "mermaid/components/VBox.h"
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
    auto view = View::create(0, 0, 450, 50);
    auto view2 = View::create(0, 0, 200, 50);
    auto view3 = View::create(0, 0, 200, 50);
    auto view4 = View::create(0, 0, 200, 50);

    view->setBackground(50, 60, 70);
    view2->setBackground(100, 0, 200);
    view3->setBackground(0, 100, 200);
    view4->setBackground(100, 180, 20);

    auto hbox = HBox::create();
    auto vbox = VBox::create();
    hbox->addChild(view);
    hbox->addChild(view2);

    vbox->addChild(hbox);
    vbox->addChild(view3);
    vbox->addChild(view4);

    app.setRootComponent(vbox);

    /* text->setText(u8"OK"); */

    std::unique_ptr<ResourceManager<Font, std::u8string>> manager(new ResourceManager<Font, std::u8string>());

    auto font =
        manager->load(u8"defaultFont", u8"/home/waldson/.local/share/fonts/Hack Regular Nerd Font Complete.ttf", 18)
            .value();
    const std::u8string label = u8"Waldson Patrício";
    auto text = Label::create(label, *font);
    text->setPosition(20, 15);
    text->setColor(Color(150, 200, 200));
    text->setSize(100, 100);
    view->addChild(text);

    /* app.setRootComponent(std::move(view)); */
    app.run();

    return 0;
}
