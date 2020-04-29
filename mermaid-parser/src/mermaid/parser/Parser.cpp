#include "mermaid/parser/Parser.h"

#include "mermaid/parser/Lexer.h"
#include "mermaid/parser/Error.h"

#include <fstream>
#include <iostream>
#include <sstream>

mermaid::parser::Parser::Parser(): dataVariables();
{
}

void mermaid::parser::Parser::parse(const std::string& filename)
{
    std::stringstream ss;
    if (filename == "-") {
        std::string line;
        while (std::getline(std::cin, line)) {
            ss << line;
            ss << "\n";
        }
    } else {
        std::ifstream file(filename);

        if (!file.good()) {
            error("Error opening file: " + filename);
        }

        std::string line;
        size_t totalLines = 0;
        while (std::getline(file, line)) {
            if (totalLines > 0) {
                ss << "\n";
            }
            totalLines++;
            ss << line;
        }
    }

    std::string contents = ss.str();

    mermaid::parser::Location location(filename);
    mermaid::parser::Lexer lexer(location, contents);

    while (!lexer.eof()) {
        lexer.consumeWhitespaces();
        doParse(lexer);
    }
}

void mermaid::parser::Parser::doParse(mermaid::parser::Lexer& lexer)
{
    if (lexer.contains("class")) {
        parseClass(lexer);
    } else if (lexer.contains("namespace")) {
        parseNamespace(lexer);
    } else if (lexer.contains("data")) {
        parseData(lexer);
    } else {
        lexer.advance();
    }
}

void mermaid::parser::Parser::parseData(mermaid::parser::Lexer& lexer)
{
    lexer.consume("data");
    lexer.consumeWhitespaces();
    lexer.consume("{");
    lexer.consumeWhitespaces();
    while (lexer.peek() != '}') {
        dataVariables.push_back(parseVariable(lexer));
    }
    lexer.consumeWhitespaces();
    lexer.consume("}");
}

bool mermaid::parser::Parser::isType(mermaid::parser::Lexer& lexer)
{
    return lexer.contains("int") 
        || lexer.contains("string")
        || lexer.contains("float")
        || lexer.contains("char")
        || lexer.contains("unsigned")
        || lexer.contains("bool");
}


std::string mermaid::parser::Parser::parseVariable(mermaid::parser::Lexer& lexer)
{
    auto type = parseType(lexer);
    lexer.consumeWhitespaces();

    auto isArray  = false;
    if (lexer.peek() == '[') {
        lexer.consume("[");
        lexer.consumeWhitespaces();
        lexer.consume("]");
        lexer.consumeWhitespaces();
        isArray = true;
    }

    auto identifier = lexer.consumeIdentifier();
    lexer.consumeWhitespaces();

    auto defaultValue = "";
    auto hasDefaultValue = false;

    if (lexer.peek() == '=') {
        hasDefaultValue = true;
        lexer.consumeWhitespaces();

        defaultValue = lexer.consumeUntil("(\\s|;)");
        lexer.consumeWhitespaces();

        if (lexer.peek() == ';') {
            lexer.consume(";");
        }
        lexer.consumeWhitespaces();
    }

    if (!hasDefaultValue) {
        auto v = mermaid::parser::Variable(type, identifier);
        v.isArray = isArray;
        return v;
    } 

    auto v = mermaid::parser::Variable(type, identifier, defaultValue);
    v.isArray = isArray;
    return v;
}

void mermaid::parser::Parser::error(mermaid::parser::Location& location, const std::string& message)
{
    throw mermaid::parser::Error(location, message);
}

void mermaid::parser::Parser::parseClass(mermaid::parser::Lexer& lexer)
{
    lexer.consume("class");
    lexer.consumeWhitespaces();
    className = lexer.consumeIdentifier();
    std::cout << "Class Name: " << className << std::endl;
    lexer.consumeWhitespaces();
    lexer.consume(";");
}

void mermaid::parser::Parser::parseNamespace(mermaid::parser::Lexer& lexer)
{
    lexer.consume("namespace");
    lexer.consumeWhitespaces();
    ns = lexer.consumeIdentifier();
    std::cout << "Namespace: " << ns << std::endl;
    lexer.consumeWhitespaces();
    lexer.consume(";");
}
