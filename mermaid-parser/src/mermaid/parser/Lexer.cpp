#include "mermaid/parser/Lexer.h"

#include "mermaid/parser/Error.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>

mermaid::parser::Lexer::Lexer(mermaid::parser::Location& location, const std::string& contents) :
    location(location), contents(contents)
{
    contentsLength = contents.length();
}

void mermaid::parser::Lexer::consumeWhitespaces()
{
    consumeWhile("( |\r|\n|\t)");
}

std::string mermaid::parser::Lexer::consumeCode()
{
    return "";
}

std::string mermaid::parser::Lexer::consumeAttribute()
{
    return "";
}

std::string mermaid::parser::Lexer::consumeUntil(const std::string& regex)
{
    std::stringstream ss;
    std::regex rg(regex, std::regex_constants::ECMAScript);


    while (!eof()) {
        auto c = peek();
        if (std::regex_match(charToString(c), rg)) {
            break;
        }
        ss << c;
        advance();
    }

    return ss.str();
}

std::string mermaid::parser::Lexer::consumeWhile(const std::string& regex)
{
    std::stringstream ss;
    std::regex rg(regex, std::regex_constants::ECMAScript);


    while (!eof()) {
        auto c = peek();
        if (!std::regex_match(charToString(c), rg)) {
            break;
        }
        ss << c;
        advance();
    }

    return ss.str();
}

std::string mermaid::parser::Lexer::consumeIdentifier()
{
    std::string firstCharacters = consumeWhile("[a-zA-Z_]");
    return firstCharacters + consumeWhile("[a-zA-Z0-9_]");
}

std::string mermaid::parser::Lexer::consume(const std::string& text)
{
    for (const char& c : text) {
        if (peek() == c) {
            advance();
        } else {
            throw mermaid::parser::Error(location,
                                         "Unexpected char. Expected:" + charToString(c) + ", found: " + charToString(peek()));
        }
    }
    return "";
}

mermaid::parser::VariableType mermaid::parser::Lexer::consumeType()
{
    if (contains("int")) {
        return mermaid::parser::VariableType::Integer;
    } else if (contains("string")) {
        return mermaid::parser::VariableType::String;
    } else if (contains("unsigned")) {
        return mermaid::parser::VariableType::Unsigned;
    } else if (contains("float")) {
        return mermaid::parser::VariableType::FloatPoint;
    } else if (contains("char")) {
        return mermaid::parser::VariableType::Character;
    } else if (contains("bool")) {
        return mermaid::parser::VariableType::Boolean;
    } else {

        throw mermaid::parser::Error(location, "Expected type, found " << charToString(peek()));
    }
}

bool mermaid::parser::Lexer::contains(const std::string& str)
{
    std::string substr = contents.substr(location.getPosition(), str.length());
    return str == substr;
}

bool mermaid::parser::Lexer::eof()
{
    return location.getPosition() >= contentsLength;
}

char mermaid::parser::Lexer::advance()
{
    if (eof()) {
        throw mermaid::parser::Error(location, "Unexpected end of file");
    }
    if (peek() == '\n') {
        location.lines();
    } else {
        location.step();
    }

    return peek();
}

char mermaid::parser::Lexer::peek()
{
    auto str = contents.substr(location.getPosition(), 1);
    return str.c_str()[0];
}

std::string mermaid::parser::Lexer::charToString(const char c)
{
    std::stringstream ss;
    ss << c;

    return ss.str();
}

mermaid::parser::Location& mermaid::parser::Lexer::getLocation()
{
    return location;
}
