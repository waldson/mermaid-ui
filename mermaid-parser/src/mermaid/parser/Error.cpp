#include "mermaid/parser/Error.h"

mermaid::parser::Error::Error(mermaid::parser::Location location, std::string error) : location(location), error(error)
{
}
std::string mermaid::parser::Error::getMessage()
{
    return error;
}

mermaid::parser::Location mermaid::parser::Error::getLocation()
{
    return location;
}
