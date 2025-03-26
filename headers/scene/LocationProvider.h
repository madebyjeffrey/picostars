//
// Created by Jeffrey Drake on 2025-03-25.
//

#ifndef LOCATIONPROVIDER_H
#define LOCATIONPROVIDER_H

#include <cmath>

#include "Types.h"

struct LocationProvider {
    virtual ~LocationProvider() = default;

    virtual auto GetPosition(Rect<int> const &parent_rect, Rect<int> const &node_rect) -> Point<int> = 0;
};

struct FixedLocationProvider final : LocationProvider {
    Point<int> position;

    explicit FixedLocationProvider(Point<int> const &position): position{position} {
    }

    FixedLocationProvider(FixedLocationProvider const &other) = default;

    FixedLocationProvider(FixedLocationProvider &&other) = default;

    auto GetPosition(Rect<int> const &parent_rect, Rect<int> const &node_rect) -> Point<int> override {
        return position;
    }
};

struct PercentageLocationProvider final : LocationProvider {
    Point<double> position;

    explicit PercentageLocationProvider(Point<double> const &position): position{position} {
    }

    PercentageLocationProvider(PercentageLocationProvider const &other) = default;

    PercentageLocationProvider(PercentageLocationProvider &&other) = default;

    auto GetPosition(Rect<int> const &parent_rect, Rect<int> const &node_rect) -> Point<int> override {
        return Point{
            .x = static_cast<int>(trunc(position.x * parent_rect.w + parent_rect.x)),
            .y = static_cast<int>(trunc(position.y * parent_rect.h + parent_rect.y))
        };
    }
};

#endif //LOCATIONPROVIDER_H
