#ifndef MERMAID_GRAPHICS_DRAW_CONTEXT_HPP
#define MERMAID_GRAPHICS_DRAW_CONTEXT_HPP

#include <span>
#include <string>
#include <utility>

namespace mermaid::graphics {

struct DrawContext
{
    virtual ~DrawContext() = default;

    virtual DrawContext& setDirty(bool dirty) = 0;
    virtual bool isDirty() const = 0;
    virtual void savePNG(const std::string& filename) = 0;
    virtual DrawContext& drawPoint(const float x, const float y, const float radius) = 0;
    virtual DrawContext& drawLine(const float x1, const float y1, const float x2, const float y2) = 0;
    virtual DrawContext& drawRectangle(const float x, const float y, const float width, const float height) = 0;
    virtual DrawContext& drawRoundedRectangle(const float x, const float y, const float width, const float height,
                                              const float radius) = 0;
    virtual DrawContext& drawCircle(const float x, const float y, const float r) = 0;
    virtual DrawContext& drawArc(const float x, const float y, const float r, const float angle1,
                                 const float angle2) = 0;
    virtual DrawContext& drawEllipse(const float x, const float y, const float rx, const float ry) = 0;
    virtual DrawContext& drawEllipticalArc(const float x, const float y, const float rx, const float ry,
                                           const float angle1, const float angle2) = 0;
    virtual DrawContext& drawRegularPolygon(const int n, const float x, const float y, const float r,
                                            const float rotation) = 0;
    // virtual DrawContext& drawImage(im image.Image, const float x, const float y int);
    // virtual DrawContext& drawImageAnchored(im image.Image, const float x, const float y int, ax, ay float64);
    virtual DrawContext& setPixel(const int x, const int y) = 0;

    virtual DrawContext& moveTo(const float x, const float y) = 0;
    virtual DrawContext& lineTo(const float x, const float y) = 0;
    virtual DrawContext& quadraticTo(const float x1, const float y1, const float x2, const float y2) = 0;
    virtual DrawContext& cubicTo(const float x1, const float y1, const float x2, const float y2, const float x3,
                                 const float y3) = 0;
    virtual DrawContext& closePath() = 0;
    virtual DrawContext& clearPath() = 0;
    virtual DrawContext& newSubPath() = 0;

    virtual DrawContext& clear() = 0;
    virtual DrawContext& stroke() = 0;
    virtual DrawContext& fill() = 0;
    virtual DrawContext& strokePreserve() = 0;
    virtual DrawContext& fillPreserve() = 0;

    virtual DrawContext& setRGB(const float r, const float g, const float b) = 0;
    virtual DrawContext& setRGBA(const float r, const float g, const float b, const float a) = 0;
    virtual DrawContext& setRGB255(const int r, const int g, const int b) = 0;
    virtual DrawContext& setRGBA255(const int r, const int g, const int b, const int a) = 0;
    // virtual DrawContext& setColor(const float c color.Color) = 0;
    virtual DrawContext& setHexColor(const std::string& hexColor) = 0;
    virtual DrawContext& setLineWidth(const float lineWidth) = 0;
    // virtual DrawContext& setLineCap(lineCap LineCap);
    // virtual DrawContext& setLineJoin(lineJoin LineJoin);
    virtual DrawContext& setDash(const std::span<float>& dashes) = 0;
    virtual DrawContext& setDashOffset(const float offset) = 0;
    virtual DrawContext& push() = 0;
    virtual DrawContext& pop() = 0;
    // virtual DrawContext& setFillRule(fillRule FillRule);

    virtual DrawContext& drawString(const std::string& s, const float x, const float y) = 0;
    virtual DrawContext& drawStringAnchored(std::string string, const float x, const float y, const float ax,
                                            const float ay) = 0;
    virtual DrawContext& drawStringWrapped(std::string string, const float x, const float y, const float ax,
                                           const float ay, const float width, const float lineSpacing /* align*/) = 0;
    virtual std::pair<float, float> measureString(std::string string) = 0;
    virtual std::pair<float, float> measureMultilineString(std::string string, float lineSpacing) = 0;
    // virtual DrawContext& wordWrap(std::string string, w float64)[] string;
    // virtual DrawContext& setFontFace(fontFace font.Face);
    // virtual DrawContext& loadFontFace(path string, points float64) error;
};

} // namespace mermaid::graphics
#endif
