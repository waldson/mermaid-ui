#include "mermaid/Application.h"

#include "mermaid/Context.h"
#include "mermaid/Event.h"
#include "mermaid/SdlWindow.h"

#include <SDL2/SDL.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>

mermaid::Application::Application(mermaid::SdlWindow& window) :
    window(window), running(false), delta(0.0f), rootComponent(nullptr)
{
}

void mermaid::Application::clear()
{
    SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(window.getRenderer());
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
        if (!hasRoot) {
            // must consume all events
            continue;
        }

        rootComponent->handleEvent(event, ctx);

        if (event.isMouseMotionEvent()) {
            handleMouseMotionEvents(e, ctx);
        } else if (event.isMouseButtonDownEvent()) {
        } else if (event.isMouseButtonUpEvent()) {
        }
    }

    return false;
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
        w->emit(u8"mouseLeave", evtMouseLeave);

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

        w->emit(u8"mouseEnter", evtMouseEnter);

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

        w->emit(u8"mouseMove", evtMouseMove);

        if (!evtMouseMove.isDefaultPrevented() && !evtMouseMove.isCanceled()) {
            w->onMouseMove(evtMouseMove);
        }
    }

    previousHoveredWidgets = currentHoveredWidgets;
}

void mermaid::Application::draw(mermaid::Context& ctx)
{
    if (rootComponent.get() == nullptr || !rootComponent->isVisible()) {
        return;
    }
    rootComponent->draw(ctx);
}

void mermaid::Application::display()
{
    SDL_RenderPresent(window.getRenderer());
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

    bool quit = false;

    mermaid::Context ctx;

    ctx.application = this;
    ctx.window = &window;
    ctx.deltaTime = delta;

    while (running && !quit) {
        begin = steady_clock::now();

        clear();
        quit = processEvents(ctx);
        update(ctx);
        draw(ctx);
        display();

        end = steady_clock::now();
        elapsed = end - begin;
        this->delta = elapsed.count();
        ctx.deltaTime = delta;

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
