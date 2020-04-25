#ifndef APPLICATION_H
#define APPLICATION_H
#include "mermaid/Context.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/Component.h"

#include <memory>

namespace mermaid {

class Application
{
  public:
    Application(mermaid::SdlWindow& window);
    void setRootComponent(std::unique_ptr<mermaid::components::Component>&& root);
    void run();

  private:
    bool processEvents();
    void clear();
    void update(mermaid::Context ctx);
    void draw(mermaid::Context ctx);
    void display();

    mermaid::SdlWindow& window;
    bool running;
    float delta;
    std::unique_ptr<mermaid::components::Component> rootComponent;
};
} // namespace mermaid
#endif
