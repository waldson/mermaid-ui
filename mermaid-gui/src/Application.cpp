#include "mermaid/Application.h"

#include "mermaid/Context.h"
#include "mermaid/Event.h"
#include "mermaid/SdlWindow.h"

#include <SDL2/SDL.h>
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
    }

    return false;
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
