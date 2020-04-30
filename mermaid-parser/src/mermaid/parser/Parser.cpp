#include "mermaid/parser/Parser.h"

#include "mermaid/parser/Lexer.h"
#include "mermaid/parser/Error.h"

#include <fstream>
#include <iostream>
#include <sstream>

mermaid::parser::Parser::Parser(): dataVariables()
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
            throw std::string("Error opening file: " + filename);
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
        if (className != "") {
            error(lexer.getLocation(), "Class already defined");
        }
        parseClass(lexer);
    } else if (lexer.contains("namespace")) {
        if (ns != "") {
            error(lexer.getLocation(), "Namespace already defined");
        }
        parseNamespace(lexer);
    } else if (lexer.contains("data")) {
        parseData(lexer);
    } else if (lexer.contains("props")) {
        parseProps(lexer);
    } else if (lexer.contains("layout")) {
        parseLayout(lexer);
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
        lexer.consumeWhitespaces();
    }
    lexer.consume("}");
}

void mermaid::parser::Parser::parseProps(mermaid::parser::Lexer& lexer)
{
    //same as data
    //TODO: avoid code repetition
    lexer.consume("props");
    lexer.consumeWhitespaces();
    lexer.consume("{");
    lexer.consumeWhitespaces();
    while (lexer.peek() != '}') {
        props.push_back(parseVariable(lexer));
        lexer.consumeWhitespaces();
    }
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


mermaid::parser::Variable mermaid::parser::Parser::parseVariable(mermaid::parser::Lexer& lexer)
{
    auto type = lexer.consumeType();
    lexer.consumeWhitespaces();

    auto isArray  = false;
    std::unordered_map<std::string, std::string> attrs;

    if (lexer.peek() == '(') {
        lexer.consume("(");
        lexer.consumeWhitespaces();
        attrs = parseDataAttributes(lexer);
        lexer.consumeWhitespaces();
        lexer.consume(")");
        lexer.consumeWhitespaces();
    }

    if (lexer.peek() == '[') {
        lexer.consume("[");
        lexer.consumeWhitespaces();
        lexer.consume("]");
        lexer.consumeWhitespaces();
        isArray = true;
    }

    auto identifier = lexer.consumeIdentifier();
    lexer.consumeWhitespaces();

    std::string defaultValue;
    auto hasDefaultValue = false;

    if (lexer.peek() == '=') {
        if (isArray) {
            error(lexer.getLocation(), "Arrays can't have default values: " + identifier + " is an array");
        }

        lexer.consume("=");
        hasDefaultValue = true;
        lexer.consumeWhitespaces();

        //TODO: validate type
        defaultValue = lexer.consumeUntil(";");
    }

    lexer.consume(";");
    lexer.consumeWhitespaces();

    if (!hasDefaultValue) {
        auto v = mermaid::parser::Variable(type, identifier);
        v.attributes = attrs;
        v.isArray = isArray;
        return v;
    } 

    auto v = mermaid::parser::Variable(type, identifier, defaultValue);
    v.isArray = isArray;
    v.attributes = attrs;
    return v;
}

std::unordered_map<std::string, std::string> mermaid::parser::Parser::parseDataAttributes(mermaid::parser::Lexer& lexer)
{
    std::unordered_map<std::string, std::string> attributes;

    while (!lexer.contains(")")) {
        lexer.consumeWhitespaces();
        std::string name = lexer.consumeIdentifier();
        lexer.consumeWhitespaces();
        if (lexer.contains("=")) {
            lexer.consume("=");
            lexer.consumeWhitespaces();
            std::string value = lexer.consumeUntil("(,|\\))");
            attributes[name] = value;
            if (lexer.contains(",")) {
                lexer.consume(",");
            }
        } else if (lexer.contains(")")) {
            attributes[name] = name;
            return attributes;
        } else if (lexer.contains(",")) {
            attributes[name] = name;
            lexer.consume(",");
        }
    }

    return attributes;
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
    lexer.consumeWhitespaces();
    lexer.consume(";");
}

void mermaid::parser::Parser::parseNamespace(mermaid::parser::Lexer& lexer)
{
    std::stringstream ss;
    lexer.consume("namespace");
    lexer.consumeWhitespaces();
    bool hasAnotherPart = true;
    do {
        ss << lexer.consumeIdentifier();
        hasAnotherPart = lexer.contains("::");
        if (hasAnotherPart) {
            ss << lexer.consume("::");
        }
    } while (hasAnotherPart);
    lexer.consumeWhitespaces();
    lexer.consume(";");
    ns = ss.str();
}


void mermaid::parser::Parser::parseLayout(mermaid::parser::Lexer& lexer)
{
    lexer.consume("layout");
    lexer.consumeWhitespaces();
    lexer.consume("{");
    lexer.consumeWhitespaces();

    rootTag = parseTag(lexer);
    lexer.consumeWhitespaces();
    lexer.consume("}");
}

mermaid::parser::Tag mermaid::parser::Parser::parseTag(mermaid::parser::Lexer& lexer)
{
    lexer.consumeWhitespaces();
    lexer.consume("<");

    mermaid::parser::Tag tag;
    tag.name = lexer.consumeIdentifier();

    lexer.consumeWhitespaces();

    std::cout << "Parsing TAG: " << tag.name << std::endl;
    tag.attributes = parseTagAttributes(lexer);

    if (lexer.contains(">")) {
        lexer.consume(">");
        lexer.consumeWhitespaces();
        while (lexer.contains("<") && !lexer.contains("</")) {
            tag.children.push_back(parseTag(lexer));
        }
        lexer.consumeWhitespaces();
    } else if (lexer.contains("/>")) {
        lexer.consume("/>");
        lexer.consumeWhitespaces();
        return tag;
    }

    lexer.consume("</");
    lexer.consume(tag.name);
    lexer.consumeWhitespaces();
    lexer.consume(">");

    return tag;
}

std::vector<mermaid::parser::Attribute>  mermaid::parser::Parser::parseTagAttributes(mermaid::parser::Lexer& lexer)
{
    std::vector<mermaid::parser::Attribute> attributes;


    while (!lexer.contains(">") && !lexer.contains("/>")) {
        lexer.consumeWhitespaces();
        attributes.push_back(parseTagAttribute(lexer));
        lexer.consumeWhitespaces();
    }
    lexer.consumeWhitespaces();

    return attributes;
}

mermaid::parser::Attribute mermaid::parser::Parser::parseTagAttribute(mermaid::parser::Lexer& lexer)
{
    lexer.consumeWhitespaces();
    mermaid::parser::Attribute attr;

    if (lexer.contains(":")) {
        lexer.consume(":");
        attr.type = mermaid::parser::AttributeType::Bind;
        attr.name = lexer.consumeIdentifier();
    } else if (lexer.contains("@")) {
        lexer.consume("@");
        attr.type = mermaid::parser::AttributeType::Callback;
        attr.name = lexer.consumeIdentifier();
    } else if (lexer.contains("mm-")) {
        lexer.consume("mm-");
        attr.type = mermaid::parser::AttributeType::Directive;
        attr.name = lexer.consumeIdentifier();
    } else {
        attr.type = mermaid::parser::AttributeType::Fixed;
        attr.name = lexer.consumeIdentifier();
    }
    lexer.consume("=");
    attr.value = parseAttrValue(lexer);

    std::cout << "Attr: " << attr.name << "=" << attr.value << std::endl;

    return attr;
}

std::string mermaid::parser::Parser::parseAttrValue(mermaid::parser::Lexer& lexer)
{
    std::stringstream ss;
    lexer.consume("\"");

    while (!lexer.contains("\"")) {
        ss << lexer.peek();
        if (lexer.contains("\\\"")) {
            ss << lexer.consume("\\\"");
        }
        lexer.advance();
    }
    lexer.consume("\"");
    lexer.consumeWhitespaces();

    return ss.str();
}

std::vector<mermaid::parser::Variable>&  mermaid::parser::Parser::getDataVariables()
{
    return dataVariables;
}

std::vector<mermaid::parser::Variable>&  mermaid::parser::Parser::getProps()
{
    return props;
}

std::string mermaid::parser::Parser::getClass()
{
    return className;
}

std::string mermaid::parser::Parser::getNamespace()
{
    return ns;
}
