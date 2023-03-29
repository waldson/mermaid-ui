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

    virtual bool isVisible() override;
    virtual void setVisible(bool visible);
    virtual void show();
    virtual void hide();
    virtual void toggleVisible();

    virtual bool isEnabled();
    virtual void setEnabled(bool enabled);
    virtual void enable();
    virtual void disable();
    virtual void toggleEnabled();

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
    std::optional<T> getOption(std::string key)
    {
        return options.get<T>(key);
    }

    template <typename T>
    std::optional<T> setOption(std::string key, T value)
    {
        return options.set(key, value);
    }

    void unsetOption(std::string key);
    bool hasOption(std::string key);
    void setOption(std::string key);

    void on(const std::string& name, mermaid::EventDispatcher::CallbackType callback);
    void off(const std::string& name);
    void emit(const std::string& name);
    void emit(const std::string& name, mermaid::Event& evt);

    inline virtual void onMouseEnter(mermaid::Event& evt)
    {
        // for (auto& w : getChildren()) {
        //     if (evt.isCanceled()) {
        //         break;
        //     }
        //     w->onMouseEnter(evt);
        // }
    }

    inline virtual void onMouseLeave(mermaid::Event& evt)
    {
        // for (auto& w : getChildren()) {
        //     if (evt.isCanceled()) {
        //         break;
        //     }
        //     w->onMouseLeave(evt);
        // }
    }

    inline virtual void onMouseMove(mermaid::Event& evt)
    {
        // for (auto& w : getChildren()) {
        //     if (evt.isCanceled()) {
        //         break;
        //     }
        //     w->onMouseMove(evt);
        // }
    }

    inline virtual void onMouseDown(mermaid::Event& evt)
    {
        // for (auto& w : getChildren()) {
        //     if (evt.isCanceled()) {
        //         break;
        //     }
        //     w->onMouseDown(evt);
        // }
    }

    inline virtual void onMouseUp(mermaid::Event& evt)
    {
        // for (auto& w : getChildren()) {
        //     if (evt.isCanceled()) {
        //         break;
        //     }
        //     w->onMouseUp(evt);
        // }
    }

    inline virtual void onClick(mermaid::Event& evt)
    {
        // for (auto& w : getChildren()) {
        //     if (evt.isCanceled()) {
        //         break;
        //     }
        //     w->onClick(evt);
        // }
    }

    inline virtual void onKeyUp(mermaid::Event& evt)
    {
        for (auto& w : getChildren()) {
            if (evt.isCanceled()) {
                break;
            }
            w->onKeyUp(evt);
        }
    }

    inline virtual void onKeyDown(mermaid::Event& evt)
    {
        for (auto& w : getChildren()) {
            if (evt.isCanceled()) {
                break;
            }
            w->onKeyDown(evt);
        }
    }

    inline virtual void onTextInput(mermaid::Event& evt)
    {
        for (auto& w : getChildren()) {
            if (evt.isCanceled()) {
                break;
            }
            w->onTextInput(evt);
        }
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
    bool enabled;

    std::weak_ptr<Widget> parent;
    std::vector<std::shared_ptr<mermaid::components::Widget>> children;
};
} // namespace mermaid::components
#endif
