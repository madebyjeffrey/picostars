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

struct position {
    std::variant<alignment, int> horizontal;
    std::variant<alignment, int> vertical;

    position(const alignment horizontal_alignment, const alignment vertical_alignment)
        : horizontal{horizontal_alignment},
          vertical{vertical_alignment} {
    }

    position(const int x, const int y): horizontal{x}, vertical{y} {
    }
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
