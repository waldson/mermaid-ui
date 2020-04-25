#ifndef MERMAID_COMPONENT_H
#define MERMAID_COMPONENT_H

#include "mermaid/Context.h"

#include <memory>

namespace mermaid::components {

class Component
{
  public:
    virtual void draw(mermaid::Context context) = 0;
    virtual void update(mermaid::Context context) = 0;
    virtual ~Component()
    {
    }
};
} // namespace mermaid::components
#endif
