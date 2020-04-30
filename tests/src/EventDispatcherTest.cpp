#include "mermaid/EventDispatcher.h"

#include "catch2/catch.hpp"
#include "mermaid/Event.h"

#include <any>
#include <string>

/* TEST_CASE("Dispatcher should emit events", "[EventDispatcher]") */
/* { */
/*     auto event = mermaid::Event::createUserEvent("TestData"); */

/*     mermaid::EventDispatcher dispatcher; */
/*     int count = 0; */
/*     dispatcher.on("testEvent", [&](mermaid::Event& evt) { */
/*         count++; */
/*         auto value = std::any_cast<const char*>(evt.getUserData().value()); */
/*         REQUIRE(value == "TestData"); */
/*     }); */

/*     dispatcher.emit("testEvent", event); */
/*     REQUIRE(count == 1); */
/* } */

TEST_CASE("Dispatcher should emit multiple events", "[EventDispatcher]")
{
    mermaid::EventDispatcher dispatcher;
    int count = 0;

    dispatcher.on("testEvent", [&](mermaid::Event& evt) { count++; });
    dispatcher.on("testEvent", [&](mermaid::Event& evt) { count++; });

    dispatcher.emit("testEvent");
    REQUIRE(count == 2);
}

TEST_CASE("Dispatcher should not dispatch canceled events", "[EventDispatcher]")
{
    mermaid::EventDispatcher dispatcher;

    int count = 0;

    dispatcher.on("testEvent", [&](mermaid::Event& evt) {
        count++;
        evt.stopPropagation();
    });

    dispatcher.on("testEvent", [&](mermaid::Event& evt) { throw "Dispatcher should not emit canceled events"; });

    dispatcher.emit("testEvent");
    REQUIRE(count == 1);
}
