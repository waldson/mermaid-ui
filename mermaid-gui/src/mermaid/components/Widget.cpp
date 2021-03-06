#include "mermaid/components/Widget.h"

mermaid::components::Widget::Widget() :
    size(0, 0), position(0, 0), padding(), margin(), border(), options(), visible(true), enabled(true)
{
}

mermaid::components::Widget::Widget(std::shared_ptr<Widget> parent) :
    size(0, 0), position(0, 0), padding(), margin(), border(), options(), visible(true), parent(parent), enabled(true)
{
}

mermaid::Size mermaid::components::Widget::getSize()
{
    return size;
}

void mermaid::components::Widget::setSize(int width, int height)
{
    size.width = width;
    size.height = height;
}

void mermaid::components::Widget::setSize(mermaid::Size size)
{
    this->size = size;
}

void mermaid::components::Widget::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void mermaid::components::Widget::setPosition(mermaid::Point p)
{
    position = p;
}

mermaid::Point mermaid::components::Widget::getPosition()
{
    return position;
}

mermaid::Padding& mermaid::components::Widget::getPadding()
{
    return padding;
}

mermaid::Margin& mermaid::components::Widget::getMargin()
{
    return margin;
}

mermaid::Border& mermaid::components::Widget::getBorder()
{
    return border;
}

bool mermaid::components::Widget::hasOption(std::string key)
{
    return options.has(key);
}

mermaid::Rect mermaid::components::Widget::getDrawRect()
{
    mermaid::Rect localRect(getPosition(), getSize());

    mermaid::Rect parentRect(0, 0, 0, 0);

    if (hasParent()) {
        parentRect = getParent().value()->getDrawRect();
    }

    mermaid::Rect rect(parentRect.x + localRect.x, parentRect.y + localRect.y, localRect.width, localRect.height);

    return rect;
}

void mermaid::components::Widget::unsetOption(std::string key)
{
    options.unset(key);
}

mermaid::Options& mermaid::components::Widget::getOptions()
{
    return options;
}

bool mermaid::components::Widget::isEnabled()
{
    return enabled;
}

void mermaid::components::Widget::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

void mermaid::components::Widget::enable()
{
    setEnabled(true);
}

void mermaid::components::Widget::disable()
{
    setEnabled(false);
}

bool mermaid::components::Widget::isVisible()
{
    return visible;
}

void mermaid::components::Widget::setVisible(bool visible)
{
    this->visible = visible;
}

void mermaid::components::Widget::show()
{
    this->setVisible(true);
}

void mermaid::components::Widget::hide()
{
    this->setVisible(false);
}

void mermaid::components::Widget::toggleEnabled()
{
    this->setEnabled(!enabled);
}

void mermaid::components::Widget::toggleVisible()
{
    this->setVisible(!visible);
}

bool mermaid::components::Widget::hasParent()
{
    return !parent.expired();
}

std::optional<std::shared_ptr<mermaid::components::Widget>> mermaid::components::Widget::getParent()
{
    if (!hasParent()) {
        return std::nullopt;
    }

    return parent.lock();
}

void mermaid::components::Widget::setParent(std::shared_ptr<Widget> parent)
{
    this->parent = parent;
}

void mermaid::components::Widget::addChild(std::shared_ptr<mermaid::components::Widget> child)
{
    children.push_back(child);
    child->setParent(shared_from_this());
}

bool mermaid::components::Widget::removeChild(std::shared_ptr<mermaid::components::Widget> child)
{
    auto item = std::find(children.begin(), children.end(), child);
    if (item == children.end()) {
        return false;
    }
    children.erase(item);
    return true;
}

bool mermaid::components::Widget::hasChild(std::shared_ptr<mermaid::components::Widget> child)
{
    auto item = std::find(children.begin(), children.end(), child);
    return item != children.end();
}

void mermaid::components::Widget::clearChildren()
{
    children.clear();
}

std::vector<std::shared_ptr<mermaid::components::Widget>>& mermaid::components::Widget::getChildren()
{
    return children;
}

void mermaid::components::Widget::draw(Context& ctx)
{
    if (!isVisible()) {
        return;
    }

    for (auto& child : children) {
        if (!child->isVisible()) {
            continue;
        }
        child->draw(ctx);
    }
}

void mermaid::components::Widget::handleEvent(mermaid::Event& event, mermaid::Context& ctx)
{
    for (auto& child : children) {
        if (event.isCanceled()) {
            break;
        }
        child->handleEvent(event, ctx);
    }
}

mermaid::Point mermaid::components::Widget::getParentPosition()
{
    if (!hasParent()) {
        return Point();
    }

    return parent.lock()->getPosition();
}

void mermaid::components::Widget::update(Context& ctx)
{
    if (!isEnabled()) {
        return;
    }

    for (auto& child : children) {
        if (!child->isEnabled()) {
            continue;
        }
        child->update(ctx);
    }
}

void mermaid::components::Widget::on(const std::string& name, mermaid::EventDispatcher::CallbackType callback)
{
    dispatcher.on(name, callback);
}

void mermaid::components::Widget::off(const std::string& name)
{
    dispatcher.off(name);
}

void mermaid::components::Widget::emit(const std::string& name)
{
    auto event = mermaid::Event::createUserEvent();
    event.target = this;
    dispatcher.emit(name, event);
}

void mermaid::components::Widget::emit(const std::string& name, mermaid::Event& evt)
{
    evt.target = this;
    dispatcher.emit(name, evt);
}
