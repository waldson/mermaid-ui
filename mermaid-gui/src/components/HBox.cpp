#include "mermaid/components/HBox.h"

mermaid::components::HBox::HBox(): rect() {}

std::shared_ptr<mermaid::components::HBox> mermaid::components::HBox::create() {
    auto hBox = new mermaid::components::HBox();
    return std::shared_ptr<mermaid::components::HBox>(hBox);
}

void mermaid::components::HBox::update(Context& ctx) {
    int width = 0;
    int maxHeight = 0;

    for (auto& child : getChildren()) {
        child->update(ctx);
        if (!child->isVisible()) {
            continue;
        }
        auto childRect = child->getDrawRect();
        child->setPosition(width, 0);
        width += childRect.width;
        if (childRect.height > maxHeight) {
            maxHeight = childRect.height;
        }
    }



    setSize(width, maxHeight);
}

