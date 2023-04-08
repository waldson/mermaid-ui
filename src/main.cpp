#include "cmrc/cmrc.hpp"
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
#include <SDL_video.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main()
{
    using namespace mermaid;
    using namespace mermaid::components;

    // std::cout << c.exists("OK") << std::endl;
    // std::cout << c.exists("./resources/fonts/Roboto Mono Nerd Font Complete.ttf") << std::endl;

    // auto a = SdlContext::create();
    // auto window = a->createWindow("Teste", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
    //                               SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

    // Application app(*window);
    Application app("Hello World", 0, 0, 1024, 1024);
    auto view = View::create(0, 0, 450, 50);
    auto view2 = View::create(0, 0, 200, 50);
    auto view3 = View::create(0, 0, 200, 100);
    auto view4 = View::create(0, 0, 200, 100);

    view->setBackground(50, 60, 70);
    view2->setBackground(100, 0, 200);
    view3->setBackground(0, 100, 200);
    view3->setBorderRadius(20);
    view4->setBackground(100, 180, 20);

    auto hbox = HBox::create(10);
    auto vbox = VBox::create(10);

    vbox->setPosition(20, 20);
    hbox->addChild(view);
    hbox->addChild(view2);

    vbox->addChild(hbox);
    vbox->addChild(view3);
    vbox->addChild(view4);

    app.setRootComponent(vbox);

    /* text->setText("OK"); */

    auto manager = std::unique_ptr<ResourceManager<std::string, Font>>(new ResourceManager<std::string, Font>());

    // auto font = manager->load("defaultFont", "./resources/fonts/Roboto-Regular.ttf", 16).value();
    // auto font = manager->load("defaultFont", "./resources/fonts/Roboto Mono Nerd Font Complete.ttf", 16).value();
    auto font = manager->load("defaultFont", "./resources/fonts/RobotoMono-Bold.ttf", 16).value();
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

    view->setBorderRadius(5);

    view->on("click", [&](Event&) {
        text->setText(texts[clicks % texts.size()]);
        clicks++;
    });

    auto lbl = "Clicks: ";
    lbl += clicks;
    view->addChild(text);
    text->setText(lbl);

    auto button = Button::create("Hide View", *font);

    button->setSize(120, 50);

    button->on("action", [&](const Event&) {
        view->toggleVisible();
        if (view->isVisible()) {
            button->setText("Hide View");
            // view->hide();
            button->setNormalColor(Color(50, 150, 50));
            button->setHoverColor(Color(50, 250, 50));
            button->setActiveColor(Color(50, 100, 50));
            button->setTextColor(Color(25, 100, 25));
        } else {
            app.getRenderer().getDrawContext().savePNG("teste.png");
            button->setText("Show View");
            // view->show();
            button->setNormalColor(Color(150, 50, 50));
            button->setHoverColor(Color(150, 0, 0));
            button->setHoverColor(Color(150, 100, 100));
            button->setHoverColor(Color(100, 25, 25));
        }
    });

    auto& context = app.getRenderer().getDrawContext();
    context.setRGBA(1, 1, 0, 1)
        .drawCircle(300, 300, 10)
        .fill()
        .setRGBA255(252, 115, 0, 255)
        .setLineWidth(2)
        .drawCircle(300, 300, 10)
        .stroke();
    context.setRGBA255(88, 108, 188, 200).drawCircle(303, 303, 10).fill();

    auto input = TextInput::create(*font);
    input->setSize(600, 40);
    //
    vbox->addChild(button);
    vbox->addChild(input);

    /* app.setRootComponent(std::move(view)); */
    app.run();

    return 0;
}
