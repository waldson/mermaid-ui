#ifndef MERMAID_ATTRIBUTE_H
#define MERMAID_ATTRIBUTE_H

#include <string>

namespace mermaid::parser {

enum class AttributeType
{
    Bind,
    Callback,
    Directive,
    Fixed
};

class Attribute
{

  public:
    Attribute()
    {
    }

    mermaid::parser::AttributeType type;
    std::string name;
    std::string value;
};

} // namespace mermaid::parser
#endif
