#ifndef MERMAID_CONTEXT_H
#define MERMAID_CONTEXT_H

namespace mermaid {

struct Application;
struct SdlWindow;

class Context
{
  public:
    SdlWindow* window;
    Application* application;
    float deltaTime;
};
} // namespace mermaid
#endif
