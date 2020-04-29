#ifndef MERMAID_VARIABLE_H
#define MERMAID_VARIABLE_H

#include <string>
#include <optional>

namespace mermaid::parser {

enum class VariableType 
{
    Integer,
    Boolean,
    FloatPoint,
    Unsigned,
    String,
    Character
};

class Variable 
{
    public:
        Variable(mermaid::parser::VariableType type, std::string name, std::string defaultValue):
            type(type), name(name), defaultValue(defaultValue), isArray(false)
    {}

        Variable(mermaid::parser::VariableType type, std::string name):
            type(type), name(name), defaultValue(std::nullopt), isArray(false)
    {}

        mermaid::parser::VariableType type;
        std::string name;
        std::optional<std::string> defaultValue;
        bool isArray;
};

} //namespace mermaid
#endif
