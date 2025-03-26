//
// Created by Jeffrey Drake on 2025-03-25.
//

#ifndef LOCATIONPROVIDER_H
#define LOCATIONPROVIDER_H

#include <cmath>
#include <utility>

#include "Types.h"

struct LocationProvider;

template<typename T>
concept LocationProviderType = std::is_base_of_v<LocationProvider, T>;

struct LocationProvider {
    virtual ~LocationProvider() = default;

    virtual auto GetPosition(Rect<int> const &parent_rect, Rect<int> const &node_rect, const std::pair<Alignment, Alignment> &content_alignment) -> Point<int> = 0;

    virtual auto GetOffset(const Rect<int> &node_rect, const std::pair<Alignment, Alignment> &content_alignment) -> Point<int> {
        auto &&offset = [](const Alignment alignment, const int s) {
            switch (alignment) {
                case Alignment::kStart:
                    return 0;
                case Alignment::kCentre:
                    return -s / 2;
                case Alignment::kEnd:
                default:
                    return -s;
            }
        };

        return {
            .x = offset(content_alignment.first, node_rect.w),
            .y = offset(content_alignment.second, node_rect.h)
        };
    }
};

struct FixedLocationProvider final : LocationProvider {
    Point<int> position;

    explicit FixedLocationProvider(Point<int> const &position): position{position} {
    }

    FixedLocationProvider(FixedLocationProvider const &other) = default;

    FixedLocationProvider(FixedLocationProvider &&other) = default;

    auto GetPosition(Rect<int> const &parent_rect, Rect<int> const &node_rect, const std::pair<Alignment, Alignment> &content_alignment) -> Point<int> override {
        return translate(position, GetOffset(node_rect, content_alignment));
    }
};

struct PercentageLocationProvider final : LocationProvider {
    Point<double> position;

    explicit PercentageLocationProvider(Point<double> const &position): position{position} {
    }

    PercentageLocationProvider(PercentageLocationProvider const &other) = default;

    PercentageLocationProvider(PercentageLocationProvider &&other) = default;

    auto GetPosition(Rect<int> const &parent_rect, Rect<int> const &node_rect, const std::pair<Alignment, Alignment> &content_alignment) -> Point<int> override {
        Point<int> base = {
            .x = static_cast<int>(trunc(parent_rect.w * (position.x / 100.0) + parent_rect.x)),
            .y = static_cast<int>(trunc(parent_rect.h * (position.y / 100.0) + parent_rect.y))
        };

        return translate(base, GetOffset(node_rect, content_alignment));
    }
};

#endif //LOCATIONPROVIDER_H
