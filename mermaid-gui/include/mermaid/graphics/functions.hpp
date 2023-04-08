#ifndef MERMAID_GRAPHICS_FUNCTIONS_HPP
#define MERMAID_GRAPHICS_FUNCTIONS_HPP

#include <span>
#include <string>

namespace mermaid::graphics {

float clamp(float value, float min, float max);
float deg2rad(float degress);
float rad2deg(float radians);

} // namespace mermaid::graphics
#endif
