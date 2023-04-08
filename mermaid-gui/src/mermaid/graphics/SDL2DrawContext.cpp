#include "mermaid/graphics/SDL2DrawContext.hpp"

#include "mermaid/graphics/functions.hpp"

#include <SDL_image.h>
#include <cairo.h>
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>

mermaid::graphics::SDL2DrawContext::SDL2DrawContext(cairo_t* cairoContext, SDL_Renderer* renderer) :
    m_cairoContext(cairoContext), m_sdlRenderer(renderer)
{
}

void mermaid::graphics::SDL2DrawContext::savePNG(const std::string& filename)
{

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    int width = 0;
    int height = 0;
    SDL_GetRendererOutputSize(m_sdlRenderer, &width, &height);

    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
    SDL_RenderReadPixels(m_sdlRenderer, NULL, surface->format->format, surface->pixels, surface->pitch);

    IMG_SavePNG(surface, filename.c_str());

    SDL_FreeSurface(surface);
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawPoint(const float x, const float y,
                                                                              const float radius)
{
    cairo_arc(m_cairoContext, x, y, radius, 0, std::numbers::pi * 2);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawLine(const float x1, const float y1,
                                                                             const float x2, const float y2)
{
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawRectangle(const float x, const float y,
                                                                                  const float width, const float height)
{
    cairo_rectangle(m_cairoContext, x, y, width, height);

    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawRoundedRectangle(
    const float x, const float y, const float width, const float height, const float radius)
{
    constexpr float degrees = std::numbers::pi / 180.0f;

    cairo_new_sub_path(m_cairoContext);
    cairo_arc(m_cairoContext, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc(m_cairoContext, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc(m_cairoContext, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc(m_cairoContext, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path(m_cairoContext);

    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawCircle(const float x, const float y,
                                                                               const float r)
{
    cairo_arc(m_cairoContext, x, y, r, 0, 2 * std::numbers::pi);

    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawArc(const float x, const float y, const float r,
                                                                            const float angle1, const float angle2)
{
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawEllipse(const float x, const float y,
                                                                                const float rx, const float ry)
{
    return drawEllipticalArc(x, y, rx, ry, 0, std::numbers::pi * 2);
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawEllipticalArc(
    const float x, const float y, const float rx, const float ry, const float angle1, const float angle2)
{
    if (rx == 0 || ry == 0) {
        return *this;
    }

    auto yScale = ry / rx;

    // from: https://www.cairographics.org/cookbook/ellipses/
    cairo_matrix_t originalMatrix;
    cairo_get_matrix(m_cairoContext, &originalMatrix);
    cairo_translate(m_cairoContext, x, y);
    cairo_scale(m_cairoContext, 1, yScale);
    cairo_translate(m_cairoContext, -x, -y);
    cairo_new_path(m_cairoContext);
    cairo_arc(m_cairoContext, x, y, rx, angle1, angle2);
    cairo_set_matrix(m_cairoContext, &originalMatrix);

    // cairo_arc(m_cairoContext, x, y, r)
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawRegularPolygon(
    const int n, const float x, const float y, const float r, const float rotation)
{
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::setPixel(const int x, const int y)
{
    // m_point.x = x;
    // m_point.y = y;
    //
    // beginDraw();
    // SDL_RenderDrawPoint(m_renderer, x, y);
    // endDraw();
    //
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::moveTo(const float x, const float y)
{
    cairo_move_to(m_cairoContext, x, y);

    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::lineTo(const float x, const float y)
{
    cairo_line_to(m_cairoContext, x, y);

    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::quadraticTo(const float x1, const float y1,
                                                                                const float x2, const float y2)
{
    // from: https://lists.cairographics.org/archives/cairo/2010-April/019691.html
    double x0, y0;
    cairo_get_current_point(m_cairoContext, &x0, &y0);
    cairo_curve_to(m_cairoContext, 2.0 / 3.0 * x1 + 1.0 / 3.0 * x0, 2.0 / 3.0 * y1 + 1.0 / 3.0 * y0,
                   2.0 / 3.0 * x1 + 1.0 / 3.0 * x2, 2.0 / 3.0 * y1 + 1.0 / 3.0 * y2, y1, y2);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::cubicTo(
    const float x1, const float y1, const float x2, const float y2, const float x3, const float y3)
{
    cairo_curve_to(m_cairoContext, x1, y1, x2, y2, x3, y3);

    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::closePath()
{
    cairo_close_path(m_cairoContext);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::clearPath()
{
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::newSubPath()
{
    cairo_new_sub_path(m_cairoContext);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::clear()
{
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::stroke()
{
    cairo_stroke(m_cairoContext);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::fill()
{
    cairo_fill(m_cairoContext);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::strokePreserve()
{
    cairo_stroke_preserve(m_cairoContext);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::fillPreserve()
{
    cairo_fill_preserve(m_cairoContext);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::setRGB(const float r, const float g, const float b)
{
    return setRGBA(r, g, b, 1.0f);
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::setRGBA(const float r, const float g, const float b,
                                                                            const float a)
{
    cairo_set_source_rgba(m_cairoContext, r, g, b, a);

    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::setRGB255(const int r, const int g, const int b)
{
    return setRGBA255(r, g, b, 255);
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::setRGBA255(const int r, const int g, const int b,
                                                                               const int a)
{
    const auto part = 1.0f / 255.0f;
    cairo_set_source_rgba(m_cairoContext, part * r, part * g, part * b, part * a);

    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::setHexColor(const std::string& hexColor)
{
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::setLineWidth(const float lineWidth)
{
    cairo_set_line_width(m_cairoContext, lineWidth);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::setDash(const std::span<float>& dashes)
{
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::setDashOffset(const float offset)
{
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::push()
{
    cairo_save(m_cairoContext);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::pop()
{
    cairo_restore(m_cairoContext);
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawString(const std::string& s, const float x,
                                                                               const float y)
{
    push();
    cairo_select_font_face(m_cairoContext, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(m_cairoContext, 16);
    cairo_move_to(m_cairoContext, x, y);
    cairo_show_text(m_cairoContext, s.c_str());
    pop();
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawStringAnchored(
    std::string string, const float x, const float y, const float ax, const float ay)
{
    return *this;
}

mermaid::graphics::DrawContext& mermaid::graphics::SDL2DrawContext::drawStringWrapped(
    std::string string, const float x, const float y, const float ax, const float ay, const float width,
    const float lineSpacing /* align*/)
{
    return *this;
}

std::pair<float, float> mermaid::graphics::SDL2DrawContext::measureString(std::string string)
{
    push();
    cairo_text_extents_t extents;
    cairo_select_font_face(m_cairoContext, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(m_cairoContext, 16);
    cairo_text_extents(m_cairoContext, string.c_str(), &extents);
    pop();

    return {extents.width, extents.height};
}

std::pair<float, float> mermaid::graphics::SDL2DrawContext::measureMultilineString(std::string string,
                                                                                   float lineSpacing)
{
    // TODO
    return {};
}
