#ifndef APPLICATION_H
#define APPLICATION_H
#include "mermaid/Context.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/Widget.h"

#include <memory>
#include <vector>

namespace mermaid {

class Application
{
  public:
    Application(mermaid::SdlWindow& window);
    void setRootComponent(std::shared_ptr<mermaid::components::Widget> root);
    std::vector<mermaid::components::Widget*> raycast(mermaid::Point& point);
    void run();

  private:
    void doRaycast(mermaid::Point& point, mermaid::components::Widget& current,
                   std::vector<mermaid::components::Widget*>& container);

    bool processEvents(mermaid::Context& ctx);
    bool hasRootComponent();
    void clear();
    void update(mermaid::Context& ctx);
    void draw(mermaid::Context& ctx);
    void display();

    mermaid::SdlWindow& window;
    bool running;
    float delta;
    std::shared_ptr<mermaid::components::Widget> rootComponent;
    std::vector<mermaid::components::Widget*> previousHoveredWidgets;

    void handleMouseMotionEvents(SDL_Event& evt, mermaid::Context& ctx);

    std::vector<mermaid::components::Widget*> included(std::vector<mermaid::components::Widget*> previous,
                                                       std::vector<mermaid::components::Widget*> current);
    std::vector<mermaid::components::Widget*> excluded(std::vector<mermaid::components::Widget*> previous,
                                                       std::vector<mermaid::components::Widget*> current);
    std::vector<mermaid::components::Widget*> kept(std::vector<mermaid::components::Widget*> previous,
                                                   std::vector<mermaid::components::Widget*> current);
};
} // namespace mermaid
#endif
