#ifndef MERMAID_ERROR_H
#define MERMAID_ERROR_H

#include "mermaid/parser/Location.h"

#include <string>

namespace mermaid::parser {

class Error
{

  public:
    Error(mermaid::parser::Location location, std::string error);
    std::string getMessage();
    mermaid::parser::Location getLocation();

  private:
    mermaid::parser::Location location;
    std::string error;
};
} // namespace mermaid::parser
#endif
