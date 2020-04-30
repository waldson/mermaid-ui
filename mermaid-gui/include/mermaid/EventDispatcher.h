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
    void on(const std::string& name, CallbackType callback);
    void off(const std::string& name);
    void emit(const std::string& name, mermaid::Event& event);
    void emit(const std::string& name);

  private:
    std::unordered_map<std::string, std::vector<CallbackType>> listeners;
};
} // namespace mermaid
#endif
