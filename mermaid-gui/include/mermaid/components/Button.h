#ifndef MERMAID_COMPONENTS_BUTTON_H
#define MERMAID_COMPONENTS_BUTTON_H

#include "mermaid/Context.h"
#include "mermaid/Core.h"
#include "mermaid/Font.h"
#include "mermaid/components/Label.h"
#include "mermaid/components/View.h"
#include "mermaid/components/Widget.h"

#include <memory>
#include <string>

namespace mermaid::components {

class Button : public Widget
{

  public:
    static std::shared_ptr<mermaid::components::Button> create(const std::u8string& text, mermaid::Font& font);

    void draw(Context& ctx) override;
    void update(Context& ctx) override;

    void setText(const std::u8string& text);
    std::u8string getText();

    mermaid::Color getNormalColor();
    void setNormalColor(mermaid::Color normalColor);

    mermaid::Color getActiveColor();
    void setActiveColor(mermaid::Color activeColor);

    mermaid::Color getDisabledColor();
    void setDisabledColor(mermaid::Color disabledColor);

    mermaid::Color getHoverColor();
    void setHoverColor(mermaid::Color hoverColor);

    mermaid::Color getTextColor();
    void setTextColor(mermaid::Color textColor);

    mermaid::Font& getFont();
    void setFont(mermaid::Font& font);

    bool isEnabled();
    void setEnabled(bool enabled);

    mermaid::Size getSize() override;
    void setSize(int width, int height) override;
    void setSize(mermaid::Size p) override;

    mermaid::Point getPosition() override;
    void setPosition(int x, int y) override;
    void setPosition(mermaid::Point p) override;

  private:
    Button(const std::u8string& text, mermaid::Font& font);
    mermaid::Color normalColor;
    mermaid::Color activeColor;
    mermaid::Color disabledColor;
    mermaid::Color hoverColor;
    mermaid::Color textColor;
    mermaid::Color* currentColor;
    bool enabled;

    std::shared_ptr<mermaid::components::View> background;
    std::shared_ptr<mermaid::components::Label> text;

    void onMouseEnter(mermaid::Event&) override;
    void onMouseLeave(mermaid::Event&) override;
    void onMouseDown(mermaid::Event&) override;
    void onMouseUp(mermaid::Event&) override;
    void onClick(mermaid::Event&) override;
};
} // namespace mermaid::components
#endif
