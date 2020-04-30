#ifndef MERMAID_PARSER_H
#define MERMAID_PARSER_H

#include "mermaid/parser/Attribute.h"
#include "mermaid/parser/Lexer.h"
#include "mermaid/parser/Tag.h"
#include "mermaid/parser/Variable.h"

#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

namespace mermaid::parser {

class Parser
{

  public:
    Parser();
    void parse(const std::string& filename);
    void parseFromString(const std::string& contents);
    std::vector<mermaid::parser::Variable>& getDataVariables();
    std::vector<mermaid::parser::Variable>& getProps();
    std::string getClass();
    std::string getNamespace();

  private:
    void doParse(mermaid::parser::Lexer& lexer);
    void parseClass(mermaid::parser::Lexer& lexer);
    void parseNamespace(mermaid::parser::Lexer& lexer);
    void parseData(mermaid::parser::Lexer& lexer);
    void parseProps(mermaid::parser::Lexer& lexer);
    std::unordered_map<std::string, std::string> parseDataAttributes(mermaid::parser::Lexer& lexer);
    void parseLayout(mermaid::parser::Lexer& lexer);
    mermaid::parser::Tag parseTag(mermaid::parser::Lexer& lexer);
    mermaid::parser::Variable parseVariable(mermaid::parser::Lexer& lexer);
    void error(mermaid::parser::Location& location, const std::string& message);
    bool isType(mermaid::parser::Lexer& lexer);
    std::vector<mermaid::parser::Attribute> parseTagAttributes(mermaid::parser::Lexer& lexer);
    mermaid::parser::Attribute parseTagAttribute(mermaid::parser::Lexer& lexer);
    std::string parseAttrValue(mermaid::parser::Lexer& lexer);
    std::string className;
    std::string ns;
    std::vector<mermaid::parser::Variable> dataVariables;
    std::vector<mermaid::parser::Variable> props;
    mermaid::parser::Tag rootTag;
};
} // namespace mermaid::parser
#endif
