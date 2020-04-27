#ifndef MERMAID_EVENTDISPATCHER_H
#define MERMAID_EVENTDISPATCHER_H

#include "mermaid/Event.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace mermaid {

class EventDispatcher
{
  public:
    using CallbackType = std::function<void(mermaid::Event&)>;
    EventDispatcher() = default;
    void on(std::u8string name, CallbackType callback);
    void off(std::u8string name);
    void emit(std::u8string name, mermaid::Event& event);
    void emit(std::u8string name);

  private:
    std::unordered_map<std::u8string, std::vector<CallbackType>> listeners;
};
} // namespace mermaid
#endif
