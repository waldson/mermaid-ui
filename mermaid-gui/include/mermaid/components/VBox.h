#ifndef MERMAID_COMPONENTS_VBOX_V
#define MERMAID_COMPONENTS_VBOX_V

#include "mermaid/Core.h"
#include "mermaid/components/Widget.h"

#include <memory>

namespace mermaid::components {

class VBox : public Widget
{
  public:
    static std::shared_ptr<mermaid::components::VBox> create(int spacing = 0);
    void update(Context& ctx) override;

  private:
    VBox(int spacing);
    int spacing;
};
} // namespace mermaid::components
#endif
