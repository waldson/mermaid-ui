#include "mermaid/components/VBox.h"

mermaid::components::VBox::VBox(): rect() {}

std::shared_ptr<mermaid::components::VBox> mermaid::components::VBox::create() {
    auto hBox = new mermaid::components::VBox();
    return std::shared_ptr<mermaid::components::VBox>(hBox);
}

void mermaid::components::VBox::update(Context& ctx) {
    int height = 0;
    int maxWidth = 0;

    for (auto& child : getChildren()) {
        child->update(ctx);
        if (!child->isVisible()) {
            continue;
        }
        auto childRect = child->getDrawRect();
        child->setPosition(0, height);

        height += childRect.height;
        if (childRect.width > maxWidth) {
            maxWidth = childRect.width;
        }
    }
    setSize(maxWidth, height);
}

