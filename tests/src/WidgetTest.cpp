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
