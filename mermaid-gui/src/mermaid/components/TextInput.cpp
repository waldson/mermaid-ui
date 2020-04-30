#include "mermaid/components/TextInput.h"

#include "SDL_clipboard.h"

#include <iostream>

mermaid::components::TextInput::TextInput(mermaid::Font& font) :
    background(mermaid::components::View::create(0, 0)), label(mermaid::components::Label::create("", font)),
    cursor(mermaid::components::Cursor::create())
{
    background->addChild(label);
    background->addChild(cursor);

    label->setColor(Color(0, 0, 0));
    background->setBackground(Color(255, 255, 255));
    /* cursor->setColor(Color(0, 0, 0)); */
    cursor->setSize(1, font.getHeight());
}

std::shared_ptr<mermaid::components::TextInput> mermaid::components::TextInput::create(mermaid::Font& font)
{
    auto textInput = new mermaid::components::TextInput(font);
    return std::shared_ptr<mermaid::components::TextInput>(textInput);
}

void mermaid::components::TextInput::update(Context& ctx)
{
    background->update(ctx);
    mermaid::components::Widget::update(ctx);
}

void mermaid::components::TextInput::onKeyUp(mermaid::Event&)
{
    /* std::cout << "Text up" << std::endl; */
}

void mermaid::components::TextInput::onKeyDown(mermaid::Event& evt)
{
    auto e = evt.getRawEvent();
    // TODO identify ctrl bound to another physical key

    if (e.key.keysym.sym == SDLK_BACKSPACE) {
        if (value.length() > 0) {
            // TODO splice instead of pop
            // TODO ctrl backspace to delete word
            setValue(value.substr(0, value.length() - 1));
        }
    } else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_LCTRL) {
        append(SDL_GetClipboardText());
    } else if (e.key.keysym.sym == SDLK_u && SDL_GetModState() & KMOD_LCTRL) {
        setValue("");
    }
}

void mermaid::components::TextInput::append(const std::string& text)
{
    auto str = value;
    str.append(text);

    setValue(str);
}

void mermaid::components::TextInput::onTextInput(mermaid::Event& evt)
{
    append(evt.getRawEvent().text.text);
}

void mermaid::components::TextInput::draw(Context& ctx)
{
    auto bgRect = background->getDrawRect();
    auto textRect = label->getDrawRect();
    auto cursorRect = cursor->getDrawRect();

    label->setPosition(10, (bgRect.height - textRect.height) / 2);
    cursor->setPosition(textRect.width + textRect.x, (bgRect.height - cursorRect.height) / 2);
    /* text->setPosition(0, 0); */

    auto parentPosition = getParentPosition();

    background->setPosition(bgRect.x + parentPosition.x, bgRect.y + parentPosition.y);
    background->draw(ctx);
    background->setPosition(bgRect.x, bgRect.y);
}

void mermaid::components::TextInput::setValue(const std::string& value)
{
    if (this->value != value) {
        this->value = value;
        label->setText(value);
    }
}

std::string mermaid::components::TextInput::getValue()
{
    return value;
}

mermaid::Size mermaid::components::TextInput::getSize()
{
    return background->getSize();
}

void mermaid::components::TextInput::setSize(int width, int height)
{
    background->setSize(width, height);
}

void mermaid::components::TextInput::setSize(mermaid::Size p)
{
    background->setSize(p);
}

mermaid::Point mermaid::components::TextInput::getPosition()
{
    return background->getPosition();
}

void mermaid::components::TextInput::setPosition(int x, int y)
{
    background->setPosition(x, y);
}

void mermaid::components::TextInput::setPosition(mermaid::Point p)
{
    background->setPosition(p);
}
