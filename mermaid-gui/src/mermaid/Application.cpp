#include "mermaid/Application.h"

#include "mermaid/Context.h"
#include "mermaid/Event.h"
#include "mermaid/SdlContext.h"
#include "mermaid/SdlWindow.h"

#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>

mermaid::Application::Application(const std::string& title, int x, int y, int width, int height) :
    running(false), delta(0.0f), rootComponent(nullptr)
{
    m_sdlContext = mermaid::SdlContext::create();
    m_window = m_sdlContext->createWindow(title, x, y, 800, 600, SDL_WINDOW_ALLOW_HIGHDPI);
}

mermaid::SdlRenderer& mermaid::Application::getRenderer()
{
    return m_window->getRenderer();
}

void mermaid::Application::clear()
{
    m_window->getRenderer().clear();
}

void mermaid::Application::update(mermaid::Context& ctx)
{
    if (rootComponent.get() == nullptr) {
        return;
    }
    rootComponent->update(ctx);
}

void mermaid::Application::setRootComponent(std::shared_ptr<mermaid::components::Widget> root)
{
    rootComponent = root;
}

bool mermaid::Application::processEvents(mermaid::Context& ctx)
{
    SDL_Event e;

    bool hasRoot = hasRootComponent();

    while (SDL_PollEvent(&e)) {
        auto event = mermaid::Event::fromRaw(e);

        if (event.isQuitEvent()) {
            return true;
        }

        if (event.isWindowEvent()) {
            m_window->getRenderer().onWindowResize(event);
        }

        if (!hasRoot) {
            // must consume all events
            continue;
        }

        rootComponent->handleEvent(event, ctx);

        if (event.isCanceled()) {
            continue;
        }

        if (event.isMouseMotionEvent()) {
            handleMouseMotionEvents(e, ctx);
        } else if (event.isMouseButtonDownEvent()) {
            handleMouseButtonDownEvents(e, ctx);
        } else if (event.isMouseButtonUpEvent()) {
            handleMouseButtonUpEvents(e, ctx);
        } else if (event.isKeyDownEvent()) {
            handleKeyDownEvent(e, ctx);
        } else if (event.isKeyUpEvent()) {
            handleKeyUpEvent(e, ctx);
        } else if (event.isTextInputEvent()) {
            handleTextInputEvent(e, ctx);
        }
    }

    return false;
}

void mermaid::Application::handleKeyDownEvent(SDL_Event& evt, mermaid::Context& ctx)
{
    // TODO: verify focus
    auto event = mermaid::Event::fromRaw(evt);
    rootComponent->onKeyDown(event);
}

void mermaid::Application::handleKeyUpEvent(SDL_Event& evt, mermaid::Context& ctx)
{
    // TODO: verify focus
    auto event = mermaid::Event::fromRaw(evt);
    rootComponent->onKeyUp(event);
}

void mermaid::Application::handleTextInputEvent(SDL_Event& evt, mermaid::Context& ctx)
{
    // TODO: verify focus
    auto event = mermaid::Event::fromRaw(evt);
    rootComponent->onTextInput(event);
}

void mermaid::Application::handleMouseButtonDownEvents(SDL_Event& e, mermaid::Context& ctx)
{
    mermaid::Point location(e.button.x, e.button.y);
    auto currentMouseDownWidgets = raycast(location);

    if (!latestMouseDownWidgets.contains(e.button.button)) {
        latestMouseDownWidgets[e.button.button] = std::vector<mermaid::components::Widget*>();
    } else {
        latestMouseDownWidgets.at(e.button.button).clear();
    }

    auto evt = mermaid::Event::fromRaw(e);

    for (auto w : currentMouseDownWidgets) {
        if (evt.isCanceled()) {
            break;
        }

        w->emit("mouseDown", evt);

        if (!evt.isDefaultPrevented() && !evt.isCanceled()) {
            w->onMouseDown(evt);
        }
    }
    latestMouseDownWidgets[e.button.button] = currentMouseDownWidgets;
}

void mermaid::Application::handleMouseButtonUpEvents(SDL_Event& e, mermaid::Context& ctx)
{
    mermaid::Point location(e.button.x, e.button.y);
    auto currentMouseUpWidgets = raycast(location);

    auto evt = mermaid::Event::fromRaw(e);

    for (auto w : currentMouseUpWidgets) {
        if (evt.isCanceled()) {
            break;
        }

        w->emit("mouseUp", evt);

        if (!evt.isDefaultPrevented() && !evt.isCanceled()) {
            w->onMouseUp(evt);
        }
    }

    auto clicked = kept(latestMouseDownWidgets[e.button.button], currentMouseUpWidgets);

    auto evtMouseClick = mermaid::Event::fromRaw(e);
    for (auto w : clicked) {
        if (evtMouseClick.isCanceled()) {
            break;
        }
        w->handleEvent(evtMouseClick, ctx);

        if (evtMouseClick.isCanceled()) {
            break;
        }

        w->emit("click", evtMouseClick);

        if (!evtMouseClick.isDefaultPrevented() && !evtMouseClick.isCanceled()) {
            w->onClick(evtMouseClick);
        }
    }

    latestMouseDownWidgets[e.button.button].clear();
}

void mermaid::Application::handleMouseMotionEvents(SDL_Event& e, mermaid::Context& ctx)
{
    mermaid::Point location(e.motion.x, e.motion.y);
    auto currentHoveredWidgets = raycast(location);
    auto keptWidgets = kept(previousHoveredWidgets, currentHoveredWidgets);
    auto includedWidgets = included(previousHoveredWidgets, currentHoveredWidgets);
    auto excludedWidgets = excluded(previousHoveredWidgets, currentHoveredWidgets);

    auto evtMouseLeave = mermaid::Event::fromRaw(e);

    for (auto w : excludedWidgets) {
        if (evtMouseLeave.isCanceled()) {
            break;
        }
        w->handleEvent(evtMouseLeave, ctx);

        if (evtMouseLeave.isCanceled()) {
            break;
        }
        w->emit("mouseLeave", evtMouseLeave);

        if (!evtMouseLeave.isDefaultPrevented() && !evtMouseLeave.isCanceled()) {
            w->onMouseLeave(evtMouseLeave);
        }
    }

    auto evtMouseEnter = mermaid::Event::fromRaw(e);
    for (auto w : includedWidgets) {
        if (evtMouseEnter.isCanceled()) {
            break;
        }

        w->handleEvent(evtMouseEnter, ctx);

        if (evtMouseEnter.isCanceled()) {
            break;
        }

        w->emit("mouseEnter", evtMouseEnter);

        if (!evtMouseEnter.isDefaultPrevented() && !evtMouseEnter.isCanceled()) {
            w->onMouseEnter(evtMouseEnter);
        }
    }

    auto evtMouseMove = mermaid::Event::fromRaw(e);

    for (auto w : keptWidgets) {
        if (evtMouseMove.isCanceled()) {
            break;
        }

        w->handleEvent(evtMouseMove, ctx);

        if (evtMouseMove.isCanceled()) {
            break;
        }

        w->emit("mouseMove", evtMouseMove);

        if (!evtMouseMove.isDefaultPrevented() && !evtMouseMove.isCanceled()) {
            w->onMouseMove(evtMouseMove);
        }
    }

    previousHoveredWidgets = currentHoveredWidgets;
}

void mermaid::Application::draw(mermaid::Context& ctx)
{
    if (!rootComponent || !rootComponent->isVisible()) {
        return;
    }

    rootComponent->draw(ctx);
}

void mermaid::Application::display()
{
    m_window->getRenderer().render();
}

void mermaid::Application::run()
{
    using namespace std::chrono;

    if (running) {
        return;
    }

    running = true;

    const auto desired_fps = 60.0f;
    const auto frame_duration = 1.0f / desired_fps;

    auto begin = steady_clock::now();
    auto end = steady_clock::now();
    duration<float, std::milli> elapsed(end - begin);
    this->delta = 0;

    bool shouldQuit = false;

    mermaid::Context ctx;

    ctx.application = this;
    ctx.window = m_window.get();
    ctx.deltaTime = delta;

    begin = steady_clock::now();
    while (running && !shouldQuit) {
        clear();
        shouldQuit = processEvents(ctx);
        update(ctx);
        draw(ctx);
        display();

        end = steady_clock::now();
        elapsed = end - begin;
        this->delta = elapsed.count() / 1000.0f;
        ctx.deltaTime = delta;

        begin = steady_clock::now();

        if (this->delta < frame_duration) {
            SDL_Delay(frame_duration - this->delta);
        }
    }
}

bool mermaid::Application::hasRootComponent()
{
    return rootComponent.get() != nullptr;
}

std::vector<mermaid::components::Widget*> mermaid::Application::raycast(mermaid::Point& point)
{
    std::vector<mermaid::components::Widget*> widgets;
    if (hasRootComponent()) {
        doRaycast(point, *rootComponent, widgets);
    }

    return widgets;
}

void mermaid::Application::doRaycast(mermaid::Point& point, mermaid::components::Widget& current,
                                     std::vector<mermaid::components::Widget*>& container)
{
    if (!current.isEnabled()) {
        return;
    }

    // children first to make it bubble instead of capturing
    for (auto& child : current.getChildren()) {
        doRaycast(point, *child, container);
    }

    auto rect = current.getDrawRect();
    if (rect.contains(point)) {
        container.push_back(&current);
    }
}

std::vector<mermaid::components::Widget*> mermaid::Application::included(
    std::vector<mermaid::components::Widget*> previous, std::vector<mermaid::components::Widget*> current)
{
    std::vector<mermaid::components::Widget*> included;
    for (auto widget : current) {
        if (std::find(previous.begin(), previous.end(), widget) == previous.end()) {
            included.push_back(widget);
        }
    }

    return included;
}

std::vector<mermaid::components::Widget*> mermaid::Application::excluded(
    std::vector<mermaid::components::Widget*> previous, std::vector<mermaid::components::Widget*> current)
{
    std::vector<mermaid::components::Widget*> excluded;
    for (auto widget : previous) {
        if (std::find(current.begin(), current.end(), widget) == current.end()) {
            excluded.push_back(widget);
        }
    }

    return excluded;
}

std::vector<mermaid::components::Widget*> mermaid::Application::kept(std::vector<mermaid::components::Widget*> previous,
                                                                     std::vector<mermaid::components::Widget*> current)
{
    std::vector<mermaid::components::Widget*> kept;
    for (auto widget : current) {
        if (std::find(previous.begin(), previous.end(), widget) != previous.end()) {
            kept.push_back(widget);
        }
    }

    return kept;
}
