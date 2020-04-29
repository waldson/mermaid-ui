#include "catch2/catch.hpp"
#include "mermaid/parser/Lexer.h"
#include "mermaid/parser/Location.h"

#include <string>

TEST_CASE("Lexer should check if next character are a specified string", "[Lexer]")
{
    std::string contents("class");
    mermaid::parser::Location loc("teste-file");
    mermaid::parser::Lexer lexer(loc, contents);

    REQUIRE(lexer.contains("class"));
    REQUIRE(!lexer.contains("Class"));
    REQUIRE(!lexer.contains("other"));
}

TEST_CASE("Lexer should fetch content while a regex is matching", "[Lexer]")
{
    std::string contents("aaa   class");
    mermaid::parser::Location loc("test-file");
    mermaid::parser::Lexer lexer(loc, contents);

    REQUIRE(lexer.consumeWhile("a") == "aaa");
}

TEST_CASE("Lexer should fetch content while a regex is not matching", "[Lexer]")
{
    std::string contents("   class");
    mermaid::parser::Location loc("test-file");
    mermaid::parser::Lexer lexer(loc, contents);

    REQUIRE(lexer.consumeUntil("[a-z]") == "   ");
    REQUIRE(lexer.peek() == 'c');
}

TEST_CASE("Lexer should consume whitespaces", "[Lexer]")
{
    std::string contents("   class");
    mermaid::parser::Location loc("test-file");
    mermaid::parser::Lexer lexer(loc, contents);
    lexer.consumeWhitespaces();
    REQUIRE(lexer.peek() == 'c');
}

/* TEST_CASE("Lexer should fetch content while a regex is not matching", "[Lexer]") */
/* { */
/*     std::string contents("   class"); */
/*     mermaid::parser::Location loc("test-file"); */
/*     mermaid::parser::Lexer lexer(loc, contents); */

/*     REQUIRE(lexer.consumeUntil(" ") == "   "); */
/* } */
