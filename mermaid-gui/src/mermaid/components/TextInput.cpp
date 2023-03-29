#include "mermaid/components/TextInput.h"

#include "SDL_clipboard.h"

#include <algorithm>
#include <cmath>
#include <iostream>

mermaid::components::TextInput::TextInput(mermaid::Font& font) :
    background(mermaid::components::View::create(0, 0)), label(mermaid::components::Label::create("", font)),
    cursor(mermaid::components::Cursor::create()), cursorPosition(0)
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

    if (e.key.keysym.sym == SDLK_LEFT) {
        if (cursorPosition > 0) {
            --cursorPosition;
        }
    } else if (e.key.keysym.sym == SDLK_RIGHT) {
        cursorPosition = std::min(static_cast<size_t>(rope.charCount()), cursorPosition + 1);
    } else if (e.key.keysym.sym == SDLK_BACKSPACE) {
        if (rope.charCount() > 0 && cursorPosition > 0) {
            // TODO ctrl backspace to delete word
            rope.erase(cursorPosition - 1, 1);
            rope.rebalance();

            setValue(rope.toString());
        }
        cursorPosition = cursorPosition > 0 ? cursorPosition - 1 : 0;
    } else if (e.key.keysym.sym == SDLK_HOME) {
        cursorPosition = 0;
    } else if (e.key.keysym.sym == SDLK_END) {
        cursorPosition = rope.charCount();
    } else if (e.key.keysym.sym == SDLK_DELETE) {
        if (rope.charCount() > 0) {
            // TODO ctrl backspace to delete word
            rope.erase(cursorPosition, 1);
            rope.rebalance();

            setValue(rope.toString());
        }
    } else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_LCTRL) {
        size_t previousSize = rope.charCount();
        rope.insert(cursorPosition, SDL_GetClipboardText());
        rope.rebalance();
        size_t currentSize = rope.charCount();
        setValue(rope.toString());
        cursorPosition += (currentSize - previousSize);
    } else if (e.key.keysym.sym == SDLK_u && SDL_GetModState() & KMOD_LCTRL) {
        rope.erase(0, cursorPosition);
        rope.rebalance();
        cursorPosition = 0;
        setValue(rope.toString());
    }
}

void mermaid::components::TextInput::append(const std::string& text)
{
    rope.insert(cursorPosition, text);
    ++cursorPosition;
    setValue(rope.toString());
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
    auto cPosition = label->calculateSize(rope.substring(0, cursorPosition));
    cursor->setPosition(textRect.x + cPosition.width, (bgRect.height - cursorRect.height) / 2);
    /* text->setPosition(0, 0); */

    auto parentPosition = getParentPosition();

    background->setPosition(bgRect.x + parentPosition.x, bgRect.y + parentPosition.y);
    background->draw(ctx);
    background->setPosition(bgRect.x, bgRect.y);
}

void mermaid::components::TextInput::setValue(const std::string& value)
{
    label->setText(value);
}

std::string mermaid::components::TextInput::getValue()
{
    return rope.toString();
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
