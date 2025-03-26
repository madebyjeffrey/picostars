//
// Created by Jeffrey Drake on 2025-03-25.
//

#ifndef TYPES_H
#define TYPES_H

#include <type_traits>

#include "SDL3/SDL.h"

template<typename T>
concept Num = std::is_integral_v<T> || std::is_floating_point_v<T>;

template<typename T>
concept Floating = std::is_floating_point_v<T>;

template<typename T>
concept Integral = std::is_integral_v<T>;

template<Num T = int>
struct Point {
    T x;
    T y;
};

template<Floating T>
struct Point<T> {
    T x;
    T y;

    template<Integral U>
    explicit operator Point<U>() const {
        return Point<U>{static_cast<U>(x), static_cast<U>(y)};
    }
};

template<Integral T>
struct Point<T> {
    T x;
    T y;

    template<Floating U>
    explicit operator Point<U>() const {
        return Point<U>{static_cast<U>(x), static_cast<U>(y)};
    }
};

template<Num T = int>
struct Size {
    T w;
    T h;
};

template<Floating T>
struct Size<T> {
    T x;
    T y;

    template<Integral U>
    explicit operator Size<U>() const {
        return Size<U>{static_cast<U>(x), static_cast<U>(y)};
    }
};

template<Integral T>
struct Size<T> {
    T x;
    T y;

    template<Floating U>
    explicit operator Size<U>() const {
        return Size<U>{static_cast<U>(x), static_cast<U>(y)};
    }
};

template<Num T = int>
struct Rect {
    T x;
    T y;
    T w;
    T h;

    template<Num S>
    static auto make(const S &x, const S &y, const S &w, const S &h) -> Rect<S> {
        return Rect<S>{x, y, w, h};
    }

    template<Num S>
    static auto make(const Point<S> position, const Size<S> size) -> Rect<S> {
        return Rect<S>{position.x, position.y, size.w, size.h};
    }

    [[nodiscard]]
    auto asFRect() const -> SDL_FRect {
        return SDL_FRect{static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)};
    }
};

template<Floating T>
struct Rect<T> {
    T x;
    T y;
    T w;
    T h;

    template<Floating S>
    static auto make(const S &x, const S &y, const S &w, const S &h) -> Rect<S> {
        return Rect<S>{x, y, w, h};
    }

    template<Floating S>
    static auto make(const Point<S> position, const Size<S> size) -> Rect<S> {
        return Rect<S>{position.x, position.y, size.w, size.h};
    }

    [[nodiscard]]
    auto asFRect() const -> SDL_FRect {
        return SDL_FRect{static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)};
    }

    template<Integral U>
    explicit operator Rect<U>() const {
        return Rect<U>{static_cast<U>(x), static_cast<U>(y), static_cast<U>(w), static_cast<U>(h)};
    }
};

template<Integral T>
struct Rect<T> {
    T x;
    T y;
    T w;
    T h;

    template<Integral S>
    static auto make(const S &x, const S &y, const S &w, const S &h) -> Rect<S> {
        return Rect<S>{x, y, w, h};
    }

    template<Integral S>
    static auto make(const Point<S> position, const Size<S> size) -> Rect<S> {
        return Rect<S>{position.x, position.y, size.w, size.h};
    }

    [[nodiscard]]
    auto asFRect() const -> SDL_FRect {
        return SDL_FRect{static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)};
    }

    template<Floating U>
    explicit operator Rect<U>() const {
        return Rect<U>{static_cast<U>(x), static_cast<U>(y), static_cast<U>(w), static_cast<U>(h)};
    }
};
#endif //TYPES_H
