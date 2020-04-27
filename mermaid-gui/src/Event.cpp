#include "mermaid/Event.h"

mermaid::Event::Event(EventType type, SDL_Event& rawEvent) :
    type(type), rawEvent(rawEvent), canceled(false), defaultPrevented(false)
{
    timestamp = SDL_GetTicks();
}

mermaid::Event::Event(EventType type, SDL_Event& rawEvent, unsigned int timestamp) :
    type(type), rawEvent(rawEvent), timestamp(timestamp), canceled(false), defaultPrevented(false)
{
}

mermaid::Event::Event(EventType type, SDL_Event& rawEvent, unsigned int timestamp, std::any userData) :
    type(type), rawEvent(rawEvent), timestamp(timestamp), userData(userData), canceled(false), defaultPrevented(false)
{
}

mermaid::Event mermaid::Event::createUserEvent(std::any data)
{
    SDL_Event sdl;
    sdl.type = SDL_USEREVENT;
    return mermaid::Event(EventType::UserEvent, sdl, SDL_GetTicks(), data);
}

mermaid::Event mermaid::Event::createUserEvent()
{
    SDL_Event sdl;
    sdl.type = SDL_USEREVENT;
    return mermaid::Event(EventType::UserEvent, sdl, SDL_GetTicks());
}

std::optional<std::any> mermaid::Event::getUserData()
{
    if (!userData.has_value()) {
        return std::nullopt;
    }

    return userData;
}

bool mermaid::Event::isWindowEvent()
{
    return type == mermaid::EventType::WindowEvent;
}

bool mermaid::Event::isMouseMotionEvent()
{
    return type == mermaid::EventType::MouseMotionEvent;
}

bool mermaid::Event::isMouseButtonDownEvent()
{
    return type == mermaid::EventType::MouseButtonDownEvent;
}

bool mermaid::Event::isMouseButtonUpEvent()
{
    return type == mermaid::EventType::MouseButtonUpEvent;
}

bool mermaid::Event::isMouseWheelEvent()
{
    return type == mermaid::EventType::MouseWheelEvent;
}

bool mermaid::Event::isQuitEvent()
{
    return type == mermaid::EventType::QuitEvent;
}

bool mermaid::Event::isTextInputEvent()
{
    return type == mermaid::EventType::TextInputEvent;
}

bool mermaid::Event::isTextEditingEvent()
{
    return type == mermaid::EventType::TextEditingEvent;
}

bool mermaid::Event::isKeyDownEvent()
{
    return type == mermaid::EventType::KeyDownEvent;
}

bool mermaid::Event::isKeyUpEvent()
{
    return type == mermaid::EventType::KeyUpEvent;
}

bool mermaid::Event::isUserEvent()
{
    return type == mermaid::EventType::UserEvent;
}

SDL_Event& mermaid::Event::getRawEvent()
{
    return rawEvent;
}

mermaid::Event mermaid::Event::fromRaw(SDL_Event& evt)
{
    mermaid::EventType type(mermaid::EventType::UnknownEvent);

    switch (evt.type) {
        case SDL_QUIT:
            type = mermaid::EventType::QuitEvent;
            break;
        case SDL_WINDOWEVENT:
            type = mermaid::EventType::WindowEvent;
            break;
        case SDL_KEYDOWN:
            type = mermaid::EventType::KeyDownEvent;
            break;

        case SDL_KEYUP:
            type = mermaid::EventType::KeyUpEvent;
            break;

        case SDL_TEXTINPUT:
            type = mermaid::EventType::TextInputEvent;
            break;
        case SDL_TEXTEDITING:
            type = mermaid::EventType::TextEditingEvent;
            break;
        case SDL_MOUSEMOTION:
            type = mermaid::EventType::MouseMotionEvent;
            break;
        case SDL_MOUSEBUTTONDOWN:
            type = mermaid::EventType::MouseButtonDownEvent;
            break;
        case SDL_MOUSEBUTTONUP:
            type = mermaid::EventType::MouseButtonUpEvent;
            break;
        case SDL_MOUSEWHEEL:
            type = mermaid::EventType::MouseWheelEvent;
            break;
    }

    return mermaid::Event(type, evt);
}

bool mermaid::Event::isDefaultPrevented()
{
    return defaultPrevented;
}

bool mermaid::Event::isCanceled()
{
    return canceled;
}

void mermaid::Event::stopPropagation()
{
    canceled = true;
}

void mermaid::Event::preventDefault()
{
    defaultPrevented = true;
}

unsigned int mermaid::Event::getTimestamp()
{
    return timestamp;
}
