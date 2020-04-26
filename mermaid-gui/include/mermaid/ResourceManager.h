#ifndef MERMAID_RESOURCEMANAGER_H
#define MERMAID_RESOURCEMANAGER_H

#include <memory>
#include <optional>
#include <unordered_map>

namespace mermaid {

template <typename Resource, typename Key>
class ResourceManager
{
  public:
    ResourceManager() = default;
    ResourceManager(const ResourceManager&) = default;
    ResourceManager& operator=(const ResourceManager&) = default;

    template <typename... Args>
    inline std::optional<Resource*> load(Key key, Args&&... args)
    {
        if (has(key)) {
            return get(key);
        }

        std::unique_ptr<Resource> resource(
            Resource::create(std::forward<Args>(args)...)
        );

        storage.emplace(key, std::move(resource));

        return get(key);
    }

    inline std::optional<Resource*> get(Key key)
    {
        if (!has(key)) {
            return std::nullopt;
        }

        return &*storage.at(key);
    }

    inline bool has(Key key)
    {
        return storage.contains(key);
    }

  private:
    std::unordered_map<Key, std::unique_ptr<Resource>> storage;
};
} // namespace mermaid
#endif
