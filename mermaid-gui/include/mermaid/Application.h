#ifndef APPLICATION_H
#define APPLICATION_H
#include "mermaid/Context.h"
#include "mermaid/SdlContext.h"
#include "mermaid/SdlRenderer.h"
#include "mermaid/SdlWindow.h"
#include "mermaid/components/Widget.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace mermaid {

class Application
{
  public:
    Application(const std::string& title, int x, int y, int width, int height);
    SdlRenderer& getRenderer();
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

    std::unique_ptr<mermaid::SdlWindow> m_window;
    std::unique_ptr<mermaid::SdlContext> m_sdlContext;
    bool running;
    float delta;
    std::shared_ptr<mermaid::components::Widget> rootComponent;
    std::vector<mermaid::components::Widget*> previousHoveredWidgets;

    void handleMouseMotionEvents(SDL_Event& evt, mermaid::Context& ctx);
    void handleMouseButtonDownEvents(SDL_Event& evt, mermaid::Context& ctx);
    void handleMouseButtonUpEvents(SDL_Event& evt, mermaid::Context& ctx);
    void handleKeyDownEvent(SDL_Event& evt, mermaid::Context& ctx);
    void handleKeyUpEvent(SDL_Event& evt, mermaid::Context& ctx);
    void handleTextInputEvent(SDL_Event& evt, mermaid::Context& ctx);

    std::vector<mermaid::components::Widget*> included(std::vector<mermaid::components::Widget*> previous,
                                                       std::vector<mermaid::components::Widget*> current);
    std::vector<mermaid::components::Widget*> excluded(std::vector<mermaid::components::Widget*> previous,
                                                       std::vector<mermaid::components::Widget*> current);
    std::vector<mermaid::components::Widget*> kept(std::vector<mermaid::components::Widget*> previous,
                                                   std::vector<mermaid::components::Widget*> current);

    std::unordered_map<int, std::vector<mermaid::components::Widget*>> latestMouseDownWidgets;
};
} // namespace mermaid
#endif
