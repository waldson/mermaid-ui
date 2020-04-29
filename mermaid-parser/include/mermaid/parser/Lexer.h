#ifndef MERMAID_LEXER_H
#define MERMAID_LEXER_H

#include "mermaid/parser/Location.h"
#include "mermaid/parser/Variable.h"

#include <istream>
#include <string>

namespace mermaid::parser {

class Lexer
{
  public:
    Lexer(mermaid::parser::Location& location, const std::string& content);
    void consumeWhitespaces();
    std::string consumeCode();
    std::string consumeAttribute();
    std::string consumeIdentifier();
    mermaid::parser::VariableType consumeType();
    std::string consumeUntil(const std::string& regex);
    std::string consumeWhile(const std::string& regex);
    std::string consume(const std::string& text);
    bool contains(const std::string& str);
    char advance();
    char peek();
    bool eof();
    std::string charToString(const char c);
    mermaid::parser::Location& getLocation();

  private:
    std::string contents;
    mermaid::parser::Location& location;
    size_t contentsLength;
};
} // namespace mermaid::parser
#endif
