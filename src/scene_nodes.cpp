//
// Created by Jeffrey Drake on 2025-03-21.
//

#include <variant>

#include "scene_nodes.h"

auto resolve_with_alignment(int parent, int child, AlignmentOffset location) -> int {
    const double parentSize = static_cast<double>(parent);
    const double childSize = static_cast<double>(child);

    double base = 0.0;

    switch (location.align) {
        case alignment::centre:
            base = (parent - child) / 2.0;
        case alignment::end:
            base = parent - child;
        case alignment::start:
        default:
            base = 0.0;
    }

    double offset = std::visit([&parentSize](auto &&arg) -> double {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, pc>) {
            return parentSize * (arg.value / 100.0);
        } else if constexpr (std::is_same_v<T, px>) {
            return arg.value;
        } else {
            return static_cast<double>(arg);
        }
    }, location.offset);

    return static_cast<int>(lround(base + offset));
}

auto image_node::get_size() const -> size {
    return size{texture->w, texture->h};
}

auto scene_node::resolve_location(rect parent) const -> rect {
    size sz = get_size();

    return {
        .x = resolve_with_alignment(parent.w, sz.w, location.horizontal) + parent.x,
        .y = resolve_with_alignment(parent.h, sz.h, location.vertical) + parent.y,
        .w = sz.w,
        .h = sz.h,
    };
}

auto image_node::render(const std::shared_ptr<SDL_Renderer> &renderer, rect parent) -> void {
    auto tw = texture->w;
    auto th = texture->h;

    auto dst = resolve_location(parent).asFRect();

    SDL_RenderTexture(renderer.get(), texture.get(), nullptr, &dst);
}
