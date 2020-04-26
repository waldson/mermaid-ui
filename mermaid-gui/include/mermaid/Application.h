#ifndef APPLICATION_H
#define APPLICATION_H
#include "mermaid/Context.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/Widget.h"

#include <memory>

namespace mermaid {

class Application
{
  public:
    Application(mermaid::SdlWindow& window);
    void setRootComponent(std::shared_ptr<mermaid::components::Widget> root);
    void run();

  private:
    bool processEvents(mermaid::Context& ctx);
    void clear();
    void update(mermaid::Context& ctx);
    void draw(mermaid::Context& ctx);
    void display();

    mermaid::SdlWindow& window;
    bool running;
    float delta;
    std::shared_ptr<mermaid::components::Widget> rootComponent;
};
} // namespace mermaid
#endif
