#include "mermaid/components/Button.h"

#include "mermaid/components/Label.h"
#include "mermaid/components/View.h"

mermaid::components::Button::Button(const std::u8string& text, mermaid::Font& font) :
    background(mermaid::components::View::create(0, 0, 0, 0)), text(mermaid::components::Label::create(text, font)),
    currentColor(nullptr)
{
    setTextColor(Color(0, 0, 0));
    setNormalColor(Color(255, 255, 255));
    setHoverColor(Color(200, 200, 200));
    setActiveColor(Color(150, 150, 150));

    this->text->setColor(textColor);

    currentColor = &normalColor;
    background->setBackground(*currentColor);
    background->addChild(this->text);
}

std::shared_ptr<mermaid::components::Button> mermaid::components::Button::create(const std::u8string& text,
                                                                                 mermaid::Font& font)
{
    auto button = new mermaid::components::Button(text, font);
    return std::shared_ptr<mermaid::components::Button>(button);
}

void mermaid::components::Button::onMouseEnter(mermaid::Event&)
{
    currentColor = &hoverColor;
    background->setBackground(*currentColor);
}

void mermaid::components::Button::onMouseLeave(mermaid::Event&)
{
    currentColor = &normalColor;
    background->setBackground(*currentColor);
}

void mermaid::components::Button::onMouseDown(mermaid::Event& evt)
{
    if (evt.getRawEvent().button.button == 1) {
        currentColor = &activeColor;
        background->setBackground(*currentColor);
    }
}

void mermaid::components::Button::onMouseUp(mermaid::Event& evt)
{
    if (evt.getRawEvent().button.button == 1) {
        currentColor = &hoverColor;
        background->setBackground(*currentColor);
    }
}

void mermaid::components::Button::onClick(mermaid::Event& evt)
{
    SDL_Event rawEvent;
    rawEvent.type = SDL_USEREVENT;
    rawEvent.button = evt.getRawEvent().button;

    mermaid::Event event(mermaid::EventType::ActionPerformedEvent, rawEvent, SDL_GetTicks());
    emit(u8"action", event);
}

void mermaid::components::Button::draw(Context& ctx)
{
    auto bgRect = background->getDrawRect();
    auto textRect = text->getDrawRect();

    text->setPosition((bgRect.width - textRect.width) / 2, (bgRect.height - textRect.height) / 2);
    /* text->setPosition(0, 0); */

    auto parentPosition = getParentPosition();

    background->setPosition(bgRect.x + parentPosition.x, bgRect.y + parentPosition.y);
    background->draw(ctx);
    background->setPosition(bgRect.x, bgRect.y);
}

void mermaid::components::Button::update(Context& ctx)
{
    background->update(ctx);
    mermaid::components::Widget::update(ctx);
}

void mermaid::components::Button::setText(const std::u8string& text)
{
    this->text->setText(text);
}

std::u8string mermaid::components::Button::getText()
{
    return this->text->getText();
}

mermaid::Color mermaid::components::Button::getNormalColor()
{
    return this->normalColor;
}

void mermaid::components::Button::setNormalColor(mermaid::Color normalColor)
{
    this->normalColor = normalColor;
}

mermaid::Color mermaid::components::Button::getActiveColor()
{
    return activeColor;
}

void mermaid::components::Button::setActiveColor(mermaid::Color activeColor)
{
    this->activeColor = activeColor;
}

mermaid::Color mermaid::components::Button::getDisabledColor()
{
    return disabledColor;
}

void mermaid::components::Button::setDisabledColor(mermaid::Color disabledColor)
{
    this->disabledColor = disabledColor;
}

mermaid::Color mermaid::components::Button::getHoverColor()
{
    return hoverColor;
}

void mermaid::components::Button::setHoverColor(mermaid::Color hoverColor)
{
    this->hoverColor = hoverColor;
}

mermaid::Color mermaid::components::Button::getTextColor()
{
    return textColor;
}

void mermaid::components::Button::setTextColor(mermaid::Color textColor)
{
    this->textColor = textColor;
}

mermaid::Font& mermaid::components::Button::getFont()
{
    return text->getFont();
}

void mermaid::components::Button::setFont(mermaid::Font& font)
{
    text->setFont(font);
}

bool mermaid::components::Button::isEnabled()
{
    return enabled;
}

void mermaid::components::Button::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

mermaid::Size mermaid::components::Button::getSize()
{
    return background->getSize();
}

void mermaid::components::Button::setSize(int width, int height)
{
    background->setSize(width, height);
}

void mermaid::components::Button::setSize(mermaid::Size p)
{
    background->setSize(p);
}

mermaid::Point mermaid::components::Button::getPosition()
{
    return background->getPosition();
}

void mermaid::components::Button::setPosition(int x, int y)
{
    background->setPosition(x, y);
}

void mermaid::components::Button::setPosition(mermaid::Point p)
{
    background->setPosition(p);
}
