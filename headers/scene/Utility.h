//
// Created by Jeffrey Drake on 2025-03-24.
//

#ifndef UTILITY_H
#define UTILITY_H
#include <variant>

enum struct Alignment {
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

using Offset = std::variant<px, pc, int>;

#endif //UTILITY_H
