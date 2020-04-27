#include "mermaid/Application.h"

#include "catch2/catch.hpp"
#include "mermaid/Core.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/View.h"

#include <SDL2/SDL.h>
#include <algorithm>

TEST_CASE("Application raycasts through widgets", "[Application]")
{
    auto window = mermaid::SdlWindow::create(u8"title", 0, 0, 1000, 1000, SDL_WINDOW_HIDDEN);
    mermaid::Application app(*window);

    auto root = mermaid::components::View::create(100, 100);

    auto raycasted = mermaid::components::View::create(10, 10, 10, 10);
    auto notRaycasted = mermaid::components::View::create(20, 20, 10, 10);

    root->addChild(raycasted);
    root->addChild(notRaycasted);
    app.setRootComponent(root);

    mermaid::Point p(15, 15);
    auto targets = app.raycast(p);

    REQUIRE(std::find(targets.begin(), targets.end(), &*root) != targets.end());
    REQUIRE(std::find(targets.begin(), targets.end(), &*raycasted) != targets.end());
    REQUIRE(std::find(targets.begin(), targets.end(), &*notRaycasted) == targets.end());
    REQUIRE(targets.size() == 2);
    REQUIRE(targets[0] == &*raycasted);
    REQUIRE(targets[1] == &*root);
}
