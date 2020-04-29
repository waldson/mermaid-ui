#ifndef MERMAID_LEXER_H
#define MERMAID_LEXER_H

#include <istream>
#include <string>

namespace mermaid::parser {

class Lexer
{
  public:
    Lexer(const std::string& filename);
    Lexer(std::istream& stream);
    void consumeWhitespaces();
    std::string consumeCode();
    std::string consumeAttribute();
    std::string consumeUntil(const std::string& regex);
    void consume(const std::string& regex);
    bool matches(const std::string& str);
    void advance();

    ~Lexer();

  private:
    int line;
    int column;
};
} // namespace mermaid::parser
#endif
