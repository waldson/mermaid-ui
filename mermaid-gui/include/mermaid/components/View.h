#ifndef MERMAID_VIEW_H
#define MERMAID_VIEW_H
#include "mermaid/Context.h"
#include "mermaid/Core.h"
#include "mermaid/components/Component.h"

#include <cstdint>
#include <memory>

namespace mermaid::components {

class View : public Component
{

  public:
    static std::unique_ptr<mermaid::components::View> create();
    static std::unique_ptr<mermaid::components::View> create(int width, int height);
    static std::unique_ptr<mermaid::components::View> create(int x, int y, int width, int height);
    void setBackground(Color color);
    void setBackground(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
    void setBackground(std::uint8_t r, std::uint8_t g, std::uint8_t b);

    void draw(Context ctx) override;
    void update(Context ctx) override;

  private:
    View(int x, int y, int width, int height);

    mermaid::Options options;
};
} // namespace mermaid::components
#endif
