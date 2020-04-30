#include "mermaid/Application.h"
#include "mermaid/Core.h"
#include "mermaid/Event.h"
#include "mermaid/Font.h"
#include "mermaid/ResourceManager.h"
#include "mermaid/components/Button.h"
#include "mermaid/components/HBox.h"
#include "mermaid/components/Label.h"
#include "mermaid/components/TextInput.h"
#include "mermaid/components/VBox.h"
#include "mermaid/components/View.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    using namespace mermaid;
    using namespace mermaid::components;

    auto a = SdlContext::create();
    auto window =
        a->createWindow("Teste", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    Application app(*window);
    auto view = View::create(0, 0, 450, 50);
    auto view2 = View::create(0, 0, 200, 50);
    auto view3 = View::create(0, 0, 200, 50);
    auto view4 = View::create(0, 0, 200, 50);

    view->setBackground(50, 60, 70);
    view2->setBackground(100, 0, 200);
    view3->setBackground(0, 100, 200);
    view4->setBackground(100, 180, 20);

    auto hbox = HBox::create(10);
    auto vbox = VBox::create(10);
    hbox->addChild(view);
    hbox->addChild(view2);

    vbox->addChild(hbox);
    vbox->addChild(view3);
    vbox->addChild(view4);

    app.setRootComponent(vbox);

    /* text->setText("OK"); */

    std::unique_ptr<ResourceManager<Font, std::string>> manager(new ResourceManager<Font, std::string>());

    auto font = manager->load("defaultFont", "/home/waldson/.local/share/fonts/Hack Regular Nerd Font Complete.ttf", 18)
                    .value();
    const std::string label = "Waldson Patrício";
    auto text = Label::create(label, *font);
    text->setPosition(20, 15);
    text->setColor(Color(150, 200, 200));
    text->setSize(100, 100);

    unsigned clicks = 0;

    std::vector<std::string> texts;
    texts.push_back("Frase 1");
    texts.push_back("Frase 2");
    texts.push_back("Teste 3");
    texts.push_back("Working 4");

    view->on("click", [&](Event& evt) {
        text->setText(texts[clicks % texts.size()]);
        clicks++;
    });

    auto lbl = "Clicks: ";
    lbl += clicks;
    view->addChild(text);
    text->setText(lbl);

    auto button = Button::create("Hide View", *font);

    button->setSize(120, 50);
    button->on("action", [&](const Event& evt) {
        view->toggleVisible();
        if (view->isVisible()) {
            button->setText("Hide View");
            /* view->hide(); */
            button->setNormalColor(Color(50, 150, 50));
        } else {
            button->setText("Show View");
            /* view->show(); */
            button->setNormalColor(Color(150, 50, 50));
        }
    });

    auto input = TextInput::create(*font);
    input->setValue("Input");
    input->setSize(300, 80);

    vbox->addChild(button);
    vbox->addChild(input);

    /* app.setRootComponent(std::move(view)); */
    app.run();

    return 0;
}
