#ifndef MERMAID_COMPONENTS_TEXTINPUT_H
#define MERMAID_COMPONENTS_TEXTINPUT_H

#include "mermaid/Context.h"
#include "mermaid/Core.h"
#include "mermaid/Font.h"
#include "mermaid/components/Cursor.h"
#include "mermaid/components/Label.h"
#include "mermaid/components/View.h"
#include "mermaid/components/Widget.h"

#include <memory>
#include <string>
#include <w5n/Rope.hpp>

namespace mermaid::components {

class TextInput : public Widget
{

  public:
    static std::shared_ptr<mermaid::components::TextInput> create(mermaid::Font& font);
    void update(Context& ctx) override;
    void draw(Context& ctx) override;

    void setValue(const std::string& text);
    std::string getValue();

    mermaid::Size getSize() override;
    void setSize(int width, int height) override;
    void setSize(mermaid::Size p) override;

    mermaid::Point getPosition() override;
    void setPosition(int x, int y) override;
    void setPosition(mermaid::Point p) override;

  private:
    TextInput(mermaid::Font& font);

    std::shared_ptr<mermaid::components::View> background;
    std::shared_ptr<mermaid::components::Label> label;
    std::shared_ptr<mermaid::components::Cursor> cursor;
    size_t cursorPosition;

    w5n::Rope rope;
    void onKeyUp(mermaid::Event&) override;
    void onKeyDown(mermaid::Event&) override;
    void onTextInput(mermaid::Event&) override;
    void append(const std::string& text);
};
} // namespace mermaid::components
#endif
