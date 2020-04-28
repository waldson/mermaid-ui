#ifndef MERMAID_VIEW_H
#define MERMAID_VIEW_H
#include "mermaid/Core.h"
#include "mermaid/SdlContext.h"
#include "mermaid/components/Component.h"
#include "mermaid/components/Widget.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace mermaid::components {

class View : public Widget
{

  public:
    static std::shared_ptr<mermaid::components::View> create();
    static std::shared_ptr<mermaid::components::View> create(int width, int height);
    static std::shared_ptr<mermaid::components::View> create(int x, int y, int width, int height);

    void setBackground(Color color);
    void setBackground(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
    void setBackground(std::uint8_t r, std::uint8_t g, std::uint8_t b);

    void draw(Context& ctx) override;

  protected:
    View(int x, int y, int width, int height);

  private:
    mermaid::Color backgroundColor;
};
} // namespace mermaid::components
#endif
