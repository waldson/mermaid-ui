#include "mermaid/components/HBox.h"

mermaid::components::HBox::HBox(int spacing) : spacing(spacing)
{
}

std::shared_ptr<mermaid::components::HBox> mermaid::components::HBox::create(int spacing)
{
    auto hBox = new mermaid::components::HBox(spacing);
    return std::shared_ptr<mermaid::components::HBox>(hBox);
}

void mermaid::components::HBox::update(Context& ctx)
{
    int width = 0;
    int maxHeight = 0;

    size_t current = 0;
    size_t count = getChildren().size();

    for (auto& child : getChildren()) {
        ++current;

        child->update(ctx);

        if (!child->isVisible()) {
            continue;
        }

        auto childRect = child->getDrawRect();
        child->setPosition(width, 0);

        width += childRect.width;

        if (spacing > 0) {
            bool isLast = current == count;
            if (!isLast) {
                width += spacing;
            }
        }

        if (childRect.height > maxHeight) {
            maxHeight = childRect.height;
        }
    }

    setSize(width, maxHeight);
}
