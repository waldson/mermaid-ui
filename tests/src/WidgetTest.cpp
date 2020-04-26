#include "catch2/catch.hpp"
#include "mermaid/components/View.h"

#include <iostream>

TEST_CASE("Parent show be set correctly", "[Widget]")
{
    auto parent = mermaid::components::View::create();
    auto child = mermaid::components::View::create();

    parent->addChild(child);

    auto maybeChild = child->getParent();
    REQUIRE(maybeChild.has_value());

    auto childParent = maybeChild.value();
    REQUIRE(childParent == parent);
}

TEST_CASE("Position must be set correctly", "[Widget]")
{
    auto view = mermaid::components::View::create();
    view->setPosition(10, 20);

    REQUIRE(view->getPosition().x == 10);
    REQUIRE(view->getPosition().y == 20);
}

TEST_CASE("Size must be set correctly", "[Widget]")
{
    auto view = mermaid::components::View::create();
    view->setSize(10, 20);

    REQUIRE(view->getSize().width == 10);
    REQUIRE(view->getSize().height == 20);
}

TEST_CASE("Visibility must be set correctly", "[Widget]")
{
    auto view = mermaid::components::View::create();

    view->hide();
    REQUIRE(!view->isVisible());

    view->show();
    REQUIRE(view->isVisible());

    view->setVisible(false);
    REQUIRE(!view->isVisible());

    view->setVisible(true);
    REQUIRE(view->isVisible());
}
