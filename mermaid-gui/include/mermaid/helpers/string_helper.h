#ifndef MERMAID_STRING_HELPER_H
#define MERMAID_STRING_HELPER_H

#include <string>

// from: https://stackoverflow.com/questions/56833000/c20-with-u8-char8-t-and-stdstring
namespace mermaid::helpers {

std::string from_u8string(const std::string& s);

std::string from_u8string(std::string&& s);

#if defined(__cpp_lib_char8_t)
std::string from_u8string(const std::u8string& s);
#endif

} // namespace mermaid::helpers

#endif
