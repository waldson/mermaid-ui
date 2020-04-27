#include "catch2/catch.hpp"
#include "mermaid/Core.h"

TEST_CASE("Construct set position and size", "[Rect]")
{
    mermaid::Rect rect(10, 20, 30, 40);
    REQUIRE(rect.x == 10);
    REQUIRE(rect.y == 20);
    REQUIRE(rect.width == 30);
    REQUIRE(rect.height == 40);
}

TEST_CASE("Rect has math operations (+, -, *, /)", "[Rect]")
{
    mermaid::Rect rect(2, 2, 10, 10);
    mermaid::Rect other(10, 10, 2, 2);

    auto summed = rect + other;
    auto subtracted = rect - other;
    auto multiplied = rect * other;
    auto divided = rect / other;

    REQUIRE(summed.x == 12);
    REQUIRE(summed.y == 12);
    REQUIRE(summed.width == 12);
    REQUIRE(summed.height == 12);

    REQUIRE(subtracted.x == -8);
    REQUIRE(subtracted.y == -8);
    REQUIRE(subtracted.width == 8);
    REQUIRE(subtracted.height == 8);

    REQUIRE(multiplied.x == 20);
    REQUIRE(multiplied.y == 20);
    REQUIRE(multiplied.width == 20);
    REQUIRE(multiplied.height == 20);

    REQUIRE(divided.x == 0);
    REQUIRE(divided.y == 0);
    REQUIRE(divided.width == 5);
    REQUIRE(divided.height == 5);
}

TEST_CASE("Rect has math operations (+=, -=, *=, /=)", "[Rect]")
{
    mermaid::Rect other(2, 2, 2, 2);

    mermaid::Rect summed(0, 0, 0, 0);
    mermaid::Rect subtracted(0, 0, 0, 0);
    mermaid::Rect multiplied(10, 10, 10, 10);
    mermaid::Rect divided(10, 10, 10, 10);

    summed += other;
    subtracted -= other;
    multiplied *= other;
    divided /= other;

    REQUIRE(summed.x == 2);
    REQUIRE(summed.y == 2);
    REQUIRE(summed.width == 2);
    REQUIRE(summed.height == 2);

    REQUIRE(subtracted.x == -2);
    REQUIRE(subtracted.y == -2);
    REQUIRE(subtracted.width == -2);
    REQUIRE(subtracted.height == -2);

    REQUIRE(multiplied.x == 20);
    REQUIRE(multiplied.y == 20);
    REQUIRE(multiplied.width == 20);
    REQUIRE(multiplied.height == 20);

    REQUIRE(divided.x == 5);
    REQUIRE(divided.y == 5);
    REQUIRE(divided.width == 5);
    REQUIRE(divided.height == 5);
}

TEST_CASE("Rect must contain point", "[Rect]")
{
    mermaid::Rect rect(0, 0, 2, 2);
    mermaid::Point p(1, 1);
    mermaid::Point p2(0, 1);
    mermaid::Point p3(3, 1);
    mermaid::Point p4(1, 3);
    mermaid::Point p5(3, 3);

    REQUIRE(rect.contains(p));
    REQUIRE(rect.contains(p2));
    REQUIRE(!rect.contains(p3));
    REQUIRE(!rect.contains(p4));
    REQUIRE(!rect.contains(p5));
}

TEST_CASE("Rect intersects other rects", "[Rect]")
{
    mermaid::Rect rect(0, 0, 2, 2);
    mermaid::Rect rect2(1, 1, 3, 3);
    mermaid::Rect rect3(3, 3, 2, 2);

    REQUIRE(rect.intersects(rect2));
    REQUIRE(!rect.intersects(rect3));
}
