#ifndef MERMAID_TAG_H
#define MERMAID_TAG_H

#include <string>
#include <vector>

#include "mermaid/parser/Attribute.h"

namespace mermaid::parser {

class Tag {
    public:
        Tag()
        {}
        std::string name;
        std::vector<mermaid::parser::Attribute>  attributes;
        std::vector<mermaid::parser::Tag> children;
  
};
} //namespace mermaid
#endif
