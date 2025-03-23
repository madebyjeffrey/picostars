//
// Created by Jeffrey Drake on 2025-03-21.
//

#ifndef ALIGNMENT_H
#define ALIGNMENT_H
#include <variant>

enum struct alignment {
    start,
    centre,
    end
};

struct pc {
    double value;
};

struct px {
    int value;
};

constexpr px operator""_px(unsigned long long int value) { return {static_cast<int>(value)}; }
constexpr pc operator""_pc(long double value) { return {static_cast<double>(value)}; }

using offset = std::variant<px, pc, int>;

struct AlignmentOffset {
    alignment align;
    offset offset;
};

struct AlignmentOffset2D {
    AlignmentOffset horizontal;
    AlignmentOffset vertical;
};

struct point {
    int x;
    int y;
};

struct size {
    int w;
    int h;
};

struct rect {
    int x;
    int y;
    int w;
    int h;

    static auto make(const int x, const int y, const int w, const int h) -> rect {
        return rect{x, y, w, h};
    }

    static auto make(const point position, const size size) -> rect {
        return rect{position.x, position.y, size.w, size.h};
    }

    [[nodiscard]]
    auto asFRect() const -> SDL_FRect {
        return SDL_FRect{static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)};
    }
};


#endif //ALIGNMENT_H
