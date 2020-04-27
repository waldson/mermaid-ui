#include "mermaid/components/VBox.h"

mermaid::components::VBox::VBox(int spacing) : spacing(spacing)
{
}

std::shared_ptr<mermaid::components::VBox> mermaid::components::VBox::create(int spacing)
{
    auto hBox = new mermaid::components::VBox(spacing);
    return std::shared_ptr<mermaid::components::VBox>(hBox);
}

void mermaid::components::VBox::update(Context& ctx)
{
    int height = 0;
    int maxWidth = 0;

    size_t current = 0;
    size_t count = getChildren().size();

    for (auto& child : getChildren()) {
        ++current;

        child->update(ctx);

        if (!child->isVisible()) {
            continue;
        }

        auto childRect = child->getDrawRect();
        child->setPosition(0, height);

        height += childRect.height;

        if (spacing > 0) {
            bool isLast = current == count;
            if (!isLast) {
                height += spacing;
            }
        }

        if (childRect.width > maxWidth) {
            maxWidth = childRect.width;
        }
    }

    setSize(maxWidth, height);
}
