#include "mermaid/EventDispatcher.h"

#include "SDL_timer.h"
#include "mermaid/Event.h"

#include <algorithm>

void mermaid::EventDispatcher::on(const std::u8string& name, mermaid::EventDispatcher::CallbackType callback)
{
    if (!listeners.contains(name)) {
        listeners[name] = std::vector<std::function<void(mermaid::Event&)>>();
    }
    listeners.at(name).push_back(callback);
}

void mermaid::EventDispatcher::off(const std::u8string& name)
{
    if (!listeners.contains(name)) {
        return;
    }
    listeners.at(name).clear();
}

void mermaid::EventDispatcher::emit(const std::u8string& name, mermaid::Event& event)
{
    if (!listeners.contains(name)) {
        return;
    }

    auto l = listeners.at(name);

    if (l.size() == 0) {
        return;
    }

    for (auto& callback : l) {
        if (event.isCanceled()) {
            break;
        }
        callback(event);
    }
}

void mermaid::EventDispatcher::emit(const std::u8string& name)
{
    auto event = mermaid::Event::createUserEvent();
    emit(name, event);
}
