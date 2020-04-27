#ifndef MERMAID_EVENT_H
#define MERMAID_EVENT_H

#include <SDL2/SDL.h>
#include <any>
#include <optional>

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
    ActionPerformedEvent,
    UnknownEvent
};

namespace components {
class Widget;
}

class Event
{
    // to set target
    friend class mermaid::components::Widget;

  public:
    Event(EventType type, SDL_Event& rawEvent);
    Event(EventType type, SDL_Event& rawEvent, unsigned int timestamp);
    Event(EventType type, SDL_Event& rawEvent, unsigned int timestamp, std::any userData);

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
    const SDL_Event& getRawEvent();
    static mermaid::Event fromRaw(SDL_Event& evt);
    void stopPropagation();
    void preventDefault();
    bool isCanceled();
    bool isDefaultPrevented();

    std::optional<std::any> getUserData();
    static Event createUserEvent(std::any data);
    static Event createUserEvent();
    unsigned int getTimestamp();
    mermaid::components::Widget* getTarget();

  private:
    SDL_Event& rawEvent;
    EventType type;
    unsigned int timestamp;
    std::any userData;
    bool canceled;
    bool defaultPrevented;
    mermaid::components::Widget* target;
};
} // namespace mermaid
#endif
