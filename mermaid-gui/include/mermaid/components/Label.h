#ifndef MERMAID_LABEL_H
#define MERMAID_LABEL_H
#include "mermaid/Context.h"
#include "mermaid/Core.h"
#include "mermaid/Font.h"
#include "mermaid/components/Widget.h"

#include <memory>
#include <string>

namespace mermaid::components {

class Label : public Widget
{

  public:
    static std::shared_ptr<mermaid::components::Label> create(std::u8string text, mermaid::Font& font);

    void setColor(Color color);
    Color getColor();
    void setFont(Font& font);
    void setText(std::u8string text);

    void draw(Context& ctx) override;
    void update(Context& ctx) override;
    void setParent(std::shared_ptr<Widget> parent) override;

    std::u8string getText();
    mermaid::Font& getFont();
    ~Label();

  private:
    Label(std::u8string text, mermaid::Font& font);
    void updateTexture(Context& ctx);
    void updateSize();

    std::u8string text;
    mermaid::Font& font;
    mermaid::Color color;
    bool dirty;
    SDL_Texture* textureCache;
};
} // namespace mermaid::components
#endif
