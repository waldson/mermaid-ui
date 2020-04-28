#ifndef MERMAID_WIDGET_H
#define MERMAID_WIDGET_H

#include "mermaid/Context.h"
#include "mermaid/Core.h"
#include "mermaid/Event.h"
#include "mermaid/EventDispatcher.h"
#include "mermaid/components/Component.h"

#include <memory>
#include <optional>
#include <vector>

namespace mermaid::components {

class Widget : public Component, public std::enable_shared_from_this<mermaid::components::Widget>
{
    friend class mermaid::Application;

  public:
    virtual void draw(mermaid::Context& context);
    virtual void update(mermaid::Context& context);
    virtual Rect getDrawRect() override;

    virtual bool isVisible() override;

    virtual ~Widget() = default;

    virtual mermaid::Size getSize();
    virtual void setSize(int width, int height);
    virtual void setSize(mermaid::Size p);

    virtual mermaid::Point getPosition();
    virtual void setPosition(int x, int y);
    virtual void setPosition(mermaid::Point p);

    mermaid::Padding& getPadding();
    mermaid::Margin& getMargin();
    mermaid::Border& getBorder();
    mermaid::Options& getOptions();

    virtual void setVisible(bool visible);
    virtual void show();
    virtual void hide();
    virtual void toggleVisibility();

    virtual bool hasParent();
    virtual void setParent(std::shared_ptr<Widget> parent);
    virtual std::optional<std::shared_ptr<Widget>> getParent();
    virtual mermaid::Point getParentPosition();

    virtual void addChild(std::shared_ptr<mermaid::components::Widget> child);
    virtual bool removeChild(std::shared_ptr<mermaid::components::Widget> child);
    virtual bool hasChild(std::shared_ptr<mermaid::components::Widget> child);
    virtual void clearChildren();

    std::vector<std::shared_ptr<mermaid::components::Widget>>& getChildren();

    template <typename T>
    std::optional<T> getOption(std::u8string key)
    {
        return options.get<T>(key);
    }

    template <typename T>
    std::optional<T> setOption(std::u8string key, T value)
    {
        return options.set(key, value);
    }

    void unsetOption(std::u8string key);
    bool hasOption(std::u8string key);
    void setOption(std::u8string key);

    void on(const std::u8string& name, mermaid::EventDispatcher::CallbackType callback);
    void off(const std::u8string& name);
    void emit(const std::u8string& name);
    void emit(const std::u8string& name, mermaid::Event& evt);

    inline virtual void onMouseEnter(mermaid::Event&)
    {
    }

    inline virtual void onMouseLeave(mermaid::Event&)
    {
    }

    inline virtual void onMouseMove(mermaid::Event&)
    {
    }

    inline virtual void onMouseDown(mermaid::Event&)
    {
    }

    inline virtual void onMouseUp(mermaid::Event&)
    {
    }

    inline virtual void onClick(mermaid::Event&)
    {
    }

    inline virtual void onKeyUp(mermaid::Event&)
    {
    }

    inline virtual void onKeyDown(mermaid::Event&)
    {
    }

    inline virtual void onTextInput(mermaid::Event&)
    {
    }

  protected:
    Widget();
    Widget(std::shared_ptr<Widget> parent);
    virtual void handleEvent(mermaid::Event& event, mermaid::Context& ctx);

  private:
    mermaid::Size size;
    mermaid::Point position;
    mermaid::Padding padding;
    mermaid::Margin margin;
    mermaid::Border border;
    mermaid::Options options;
    mermaid::EventDispatcher dispatcher;

    bool visible;

    std::weak_ptr<Widget> parent;
    std::vector<std::shared_ptr<mermaid::components::Widget>> children;
};
} // namespace mermaid::components
#endif
