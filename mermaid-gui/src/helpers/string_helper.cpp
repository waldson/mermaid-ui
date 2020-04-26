#include "mermaid/helpers/string_helper.h"

#include <string>

std::string mermaid::helpers::from_u8string(const std::string& s)
{
    return s;
}

std::string mermaid::helpers::from_u8string(std::string&& s)
{
    return std::move(s);
}

#if defined(__cpp_lib_char8_t)
std::string mermaid::helpers::from_u8string(const std::u8string& s)
{
    return std::string(s.begin(), s.end());
}
#endif
