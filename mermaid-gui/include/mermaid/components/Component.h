#ifndef MERMAID_COMPONENT_H
#define MERMAID_COMPONENT_H

#include "mermaid/Context.h"
#include "mermaid/Core.h"

#include <memory>

namespace mermaid::components {

class Component
{
  public:
    virtual void draw(mermaid::Context& context) = 0;
    virtual void update(mermaid::Context& context) = 0;
    virtual Rect getDrawRect() = 0;
    virtual ~Component() = default;
};
} // namespace mermaid::components
#endif
