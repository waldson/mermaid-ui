#ifndef MERMAID_WIDGET_H
#define MERMAID_WIDGET_H

#include "mermaid/Context.h"
#include "mermaid/Core.h"
#include "mermaid/components/Component.h"

#include <memory>
#include <optional>

namespace mermaid::components {

class Widget : public Component
{

  public:
    virtual void draw(mermaid::Context& context) = 0;
    virtual void update(mermaid::Context& context) = 0;
    virtual Rect getDrawRect() = 0;

    bool isVisible() override;

    virtual ~Widget() = default;

    mermaid::Size& getSize();
    void setSize(int width, int height);
    void setSize(mermaid::Size p);

    mermaid::Point& getPosition();
    void setPosition(int x, int y);
    void setPosition(mermaid::Point p);

    mermaid::Padding& getPadding();
    mermaid::Margin& getMargin();
    mermaid::Border& getBorder();
    mermaid::Options& getOptions();

    void setVisible(bool visible);
    void show();
    void hide();
    void toggleVisibility();

    void setParent(std::shared_ptr<Widget> parent);
    std::optional<std::shared_ptr<Widget>> getParent();

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

  protected:
    Widget();
    Widget(std::shared_ptr<Widget> parent);

  private:
    mermaid::Size size;
    mermaid::Point position;
    mermaid::Padding padding;
    mermaid::Margin margin;
    mermaid::Border border;
    mermaid::Options options;
    bool visible;
    std::weak_ptr<Widget> parent;
};
} // namespace mermaid::components
#endif
