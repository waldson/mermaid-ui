#include "mermaid/graphics//functions.hpp"

#include <algorithm>
#include <numbers>

float mermaid::graphics::clamp(float value, float min, float max)
{
    return std::clamp(value, min, max);
}

float mermaid::graphics::deg2rad(float degress)
{
    return degress * std::numbers::pi / 180;
}

float mermaid::graphics::rad2deg(float radians)
{
    return radians * 180 / std::numbers::pi;
}
