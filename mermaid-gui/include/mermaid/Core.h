#ifndef MERMAID_CORE_H
#define MERMAID_CORE_H

#include <SDL2/SDL.h>
#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

namespace mermaid {

using String = std::u8string;

struct Size
{
    int width;
    int height;

    Size() : width(0), height(0)
    {
    }

    Size(int w, int h) : width(w), height(h)
    {
    }
};

struct Point
{
    int x;
    int y;

    Point() : x(0), y(0)
    {
    }

    Point(int x, int y) : x(x), y(y)
    {
    }
};

struct Rect
{
    int x;
    int y;
    int width;
    int height;

    Rect() : x(0), y(0), width(0), height(0)
    {
    }

    Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
    {
    }

    Rect(int width, int height) : x(0), y(0), width(width), height(height)
    {
    }

    Rect(mermaid::Point position, mermaid::Size size) :
        x(position.x), y(position.y), width(size.width), height(size.height)
    {
    }

    inline Rect operator+(const Rect& other)
    {
        return Rect(x + other.x, y + other.y, width + other.width, height + other.height);
    }

    inline Rect operator-(const Rect& other)
    {
        return Rect(x - other.x, y - other.y, width - other.width, height - other.height);
    }

    inline Rect operator*(const Rect& other)
    {
        return Rect(x * other.x, y * other.y, width * other.width, height * other.height);
    }

    inline Rect operator/(const Rect& other)
    {
        return Rect(x / other.x, y / other.y, width / other.width, height / other.height);
    }

    inline Rect& operator+=(const Rect& other)
    {
        x += other.x;
        y += other.y;
        width += other.width;
        height += other.height;
        return *this;
    }

    inline Rect& operator-=(const Rect& other)
    {
        x -= other.x;
        y -= other.y;
        width -= other.width;
        height -= other.height;
        return *this;
    }

    inline Rect& operator*=(const Rect& other)
    {
        x *= other.x;
        y *= other.y;
        width *= other.width;
        height *= other.height;
        return *this;
    }

    inline Rect& operator/=(const Rect& other)
    {
        x /= other.x;
        y /= other.y;
        width /= other.width;
        height /= other.height;
        return *this;
    }

    SDL_Rect toSdlRect()
    {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
        return rect;
    }
};

struct Color
{
    std::int8_t r;
    std::int8_t g;
    std::int8_t b;
    std::int8_t a;

    Color() : r(0), g(0), b(0), a(255)
    {
    }

    Color(std::uint8_t rgb) : r(rgb), g(rgb), b(rgb), a(255)
    {
    }

    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b) : r(r), g(g), b(b), a(255)
    {
    }

    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) : r(r), g(g), b(b), a(a)
    {
    }

    SDL_Color toSdlColor()
    {
        SDL_Color color;

        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;

        return color;
    }
};

template <typename T>
struct BoxProperties
{
    T top;
    T bottom;
    T left;
    T right;

    void set_x(T value)
    {
        top = value;
        bottom = value;
    }

    void set_y(T value)
    {
        left = value;
        right = value;
    }

    void set(T top, T right, T bottom, T left)
    {
        this->top = top;
        this->bottom = bottom;
        this->left = left;
        this->right = right;
    }

    void set_all(T value)
    {
        top = value;
        bottom = value;
        left = value;
        right = value;
    }
};

template <>
struct BoxProperties<int>
{
    int top;
    int bottom;
    int left;
    int right;

    BoxProperties() : top(0), bottom(0), left(0), right(0)
    {
    }

    void set_x(int value)
    {
        top = value;
        bottom = value;
    }

    void set_y(int value)
    {
        left = value;
        right = value;
    }

    void set(int top, int right, int bottom, int left)
    {
        this->top = top;
        this->bottom = bottom;
        this->left = left;
        this->right = right;
    }

    void set_all(int value)
    {
        top = value;
        bottom = value;
        left = value;
        right = value;
    }
};

struct Border
{
    BoxProperties<int> size;
    BoxProperties<Color> color;
};

// TODO: border
using Margin = BoxProperties<int>;
using Padding = BoxProperties<int>;

using Value = std::variant<std::u8string, int, float, bool, BoxProperties<int>, Border, Color, Size, Point>;

class Options
{
  public:
    template <typename T>
    std::optional<T> get(std::u8string key)
    {
        if (!options.contains(key) || !std::holds_alternative<T>(options[key])) {
            return std::nullopt;
        }

        return std::get<T>(options[key]);
    }

    bool has(std::u8string key)
    {
        return options.contains(key);
    }

    void unset(std::u8string key)
    {
        if (has(key)) {
            options.erase(key);
        }
    }

    void set(std::u8string key, std::u8string value)
    {
        options[key] = value;
    }

    void set(std::u8string key, const char8_t* value)
    {
        options[key] = std::u8string(value);
    }

    void set(std::u8string key, int value)
    {
        options[key] = value;
    }

    void set(std::u8string key, bool value)
    {
        options[key] = value;
    }

    void set(std::u8string key, float value)
    {
        options[key] = value;
    }

    void set(std::u8string key, BoxProperties<int> value)
    {
        options[key] = value;
    }

    void set(std::u8string key, Border value)
    {
        options[key] = value;
    }

    void set(std::u8string key, Color value)
    {
        options[key] = value;
    }

    void set(std::u8string key, Size value)
    {
        options[key] = value;
    }

    void set(std::u8string key, Point value)
    {
        options[key] = value;
    }

  private:
    std::unordered_map<std::u8string, Value> options;
};

} // namespace mermaid
#endif
