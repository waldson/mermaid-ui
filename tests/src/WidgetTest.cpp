#include "catch2/catch.hpp"
#include "mermaid/Core.h"
#include "mermaid/components/View.h"

TEST_CASE("Parent show be set correctly", "[Widget]")
{
    auto parent = mermaid::components::View::create();
    auto child = mermaid::components::View::create();

    parent->addChild(child);

    auto maybeChild = child->getParent();
    REQUIRE(maybeChild.has_value());
    REQUIRE(child->hasParent());

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

TEST_CASE("ViewRect must reflect position and size", "[Widget]")
{
    auto view = mermaid::components::View::create();
    view->setPosition(10, 20);
    view->setSize(30, 40);

    auto rect = view->getDrawRect();

    REQUIRE(rect.x == 10);
    REQUIRE(rect.y == 20);
    REQUIRE(rect.width == 30);
    REQUIRE(rect.height == 40);
}

TEST_CASE("Widget drawRect must be relative to its parent", "[Widget]")
{
    auto parent = mermaid::components::View::create();
    parent->setPosition(10, 20);

    auto child = mermaid::components::View::create();
    child->setPosition(10, 0);

    parent->addChild(child);

    auto rect = child->getDrawRect();

    REQUIRE(rect.x == 20);
    REQUIRE(rect.y == 20);
}
