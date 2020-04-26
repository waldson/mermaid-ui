#ifndef MERMAID_COMPONENTS_HBOX_H
#define MERMAID_COMPONENTS_HBOX_H

#include "mermaid/Core.h"
#include "mermaid/components/Widget.h"

#include <memory>

namespace mermaid::components {

class HBox: public Widget {
  public:
    static std::shared_ptr<mermaid::components::HBox> create();
    void update(Context& ctx) override;

  private:
    HBox();
    mermaid::Rect rect;

};
} //namespace mermaid::components
#endif
