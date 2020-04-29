#ifndef MERMAID_PARSER_H
#define MERMAID_PARSER_H

#include "mermaid/parser/Lexer.h"
#include "mermaid/parser/Variable.h"

#include <istream>
#include <string>
#include <vector>

namespace mermaid::parser {

class Parser
{

  public:
    Parser();
    void parse(const std::string& filename);

  private:
    void doParse(mermaid::parser::Lexer& lexer);
    void parseClass(mermaid::parser::Lexer& lexer);
    void parseNamespace(mermaid::parser::Lexer& lexer);
    void parseData(mermaid::parser::Lexer& lexer);
    mermaid::parser::Variable parseVariable(mermaid::parser::Lexer& lexer);
    void error(mermaid::parser::Location& location, const std::string& message);
    bool isType(mermaid::parser::Lexer& lexer);
    mermaid-parser::include::mermaid::parser
    std::string className;
    std::string ns;
    std::vector<mermaid::parser::Variable> dataVariables;
};
} // namespace mermaid::parser
#endif
