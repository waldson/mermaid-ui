#ifndef MERMAID_COMPONENTS_CURSOR_H
#define MERMAID_COMPONENTS_CURSOR_H

#include "mermaid/Core.h"
#include "mermaid/components/View.h"

#include <memory>

namespace mermaid::components {

class Cursor : public View
{

    Cursor();

  public:
    static std::shared_ptr<mermaid::components::Cursor> create();
    void update(Context& ctx) override;

    mermaid::Color color;
    float blinkInterval;
    float elapsedTime;
    bool up;
};
} // namespace mermaid::components
#endif
