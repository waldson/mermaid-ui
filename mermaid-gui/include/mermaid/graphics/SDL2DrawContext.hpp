#ifndef MERMAID_GRAPHICS_SDL2_DRAW_CONTEXT_HPP
#define MERMAID_GRAPHICS_SDL2_DRAW_CONTEXT_HPP

#include "mermaid/graphics/DrawContext.hpp"

#include <SDL_render.h>
#include <cairo.h>
#include <memory>
#include <span>
#include <string>

namespace mermaid::graphics {

class SDL2DrawContext : public DrawContext
{
  public:
    SDL2DrawContext(cairo_t* cairoContext, SDL_Renderer* renderer);
    virtual ~SDL2DrawContext() = default;

    virtual void savePNG(const std::string& filename) override;
    virtual DrawContext& drawPoint(const float x, const float y, const float radius) override;
    virtual DrawContext& drawLine(const float x1, const float y1, const float x2, const float y2) override;
    virtual DrawContext& drawRectangle(const float x, const float y, const float width, const float height) override;
    virtual DrawContext& drawRoundedRectangle(const float x, const float y, const float width, const float height,
                                              const float radius) override;
    virtual DrawContext& drawCircle(const float x, const float y, const float r) override;
    virtual DrawContext& drawArc(const float x, const float y, const float r, const float angle1,
                                 const float angle2) override;
    virtual DrawContext& drawEllipse(const float x, const float y, const float rx, const float ry) override;
    virtual DrawContext& drawEllipticalArc(const float x, const float y, const float rx, const float ry,
                                           const float angle1, const float angle2) override;
    virtual DrawContext& drawRegularPolygon(const int n, const float x, const float y, const float r,
                                            const float rotation) override;
    virtual DrawContext& setPixel(const int x, const int y) override;

    virtual DrawContext& moveTo(const float x, const float y) override;
    virtual DrawContext& lineTo(const float x, const float y) override;
    virtual DrawContext& quadraticTo(const float x1, const float y1, const float x2, const float y2) override;
    virtual DrawContext& cubicTo(const float x1, const float y1, const float x2, const float y2, const float x3,
                                 const float y3) override;
    virtual DrawContext& closePath() override;
    virtual DrawContext& clearPath() override;
    virtual DrawContext& newSubPath() override;

    virtual DrawContext& clear() override;
    virtual DrawContext& stroke() override;
    virtual DrawContext& fill() override;
    virtual DrawContext& strokePreserve() override;
    virtual DrawContext& fillPreserve() override;

    virtual DrawContext& setRGB(const float r, const float g, const float b) override;
    virtual DrawContext& setRGBA(const float r, const float g, const float b, const float a) override;
    virtual DrawContext& setRGB255(const int r, const int g, const int b) override;
    virtual DrawContext& setRGBA255(const int r, const int g, const int b, const int a) override;
    virtual DrawContext& setHexColor(const std::string& hexColor) override;
    virtual DrawContext& setLineWidth(const float lineWidth) override;
    virtual DrawContext& setDash(const std::span<float>& dashes) override;
    virtual DrawContext& setDashOffset(const float offset) override;
    virtual DrawContext& push() override;
    virtual DrawContext& pop() override;

    virtual DrawContext& drawString(const std::string& s, const float x, const float y) override;
    virtual DrawContext& drawStringAnchored(std::string string, const float x, const float y, const float ax,
                                            const float ay) override;
    virtual DrawContext& drawStringWrapped(std::string string, const float x, const float y, const float ax,
                                           const float ay, const float width,
                                           const float lineSpacing /* align*/) override;
    virtual std::pair<float, float> measureString(std::string string) override;
    virtual std::pair<float, float> measureMultilineString(std::string string, float lineSpacing) override;

  private:
    cairo_t* m_cairoContext;
    SDL_Renderer* m_sdlRenderer;
};

} // namespace mermaid::graphics
#endif
