#ifndef MERMAID_EVENT_H
#define MERMAID_EVENT_H

#include <SDL2/SDL.h>

namespace mermaid {

enum class EventType
{
    WindowEvent,
    MouseMotionEvent,
    MouseButtonDownEvent,
    MouseButtonUpEvent,
    MouseWheelEvent,
    QuitEvent,
    TextInputEvent,
    TextEditingEvent,
    KeyDownEvent,
    KeyUpEvent,
    UserEvent,
    UnknownEvent
};

class Event
{
  public:
    Event(EventType type, SDL_Event& rawEvent);
    bool isWindowEvent();
    bool isMouseMotionEvent();
    bool isMouseButtonDownEvent();
    bool isMouseButtonUpEvent();
    bool isMouseWheelEvent();
    bool isQuitEvent();
    bool isTextInputEvent();
    bool isTextEditingEvent();
    bool isKeyDownEvent();
    bool isKeyUpEvent();
    bool isUserEvent();
    SDL_Event& getRawEvent();
    static mermaid::Event fromRaw(SDL_Event& evt);

  private:
    SDL_Event& rawEvent;
    EventType type;
};
} // namespace mermaid
#endif
