#ifndef MERMAID_CODEGENERATOR_H
#define MERMAID_CODEGENERATOR_H

#include "mermaid/parser/Parser.h"

#include <string>

namespace mermaid::parser {

class CodeGenerator
{

  public:
    CodeGenerator();
    std::string generateHeader(const std::string& filename);
    std::string generateImplementation(const std::string& filename);

  private:
    std::string doGenerateHeader(mermaid::parser::Parser& parser);
    std::string doGenerateImplementation(mermaid::parser::Parser& parser);
    mermaid::parser::Parser parse(const std::string& filename);
};

} // namespace mermaid::parser
#endif
