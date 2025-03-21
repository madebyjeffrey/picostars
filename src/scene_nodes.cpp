//
// Created by Jeffrey Drake on 2025-03-21.
//

#include <variant>

#include "scene_nodes.h"

auto resolve_with_alignment(int parent, int child, std::variant<alignment, int> position) -> int {
    return std::visit([&parent, &child]<typename T0>(T0 &&pos) -> int {
        using T = std::decay_t<T0>;

        if constexpr (std::is_same_v<T, alignment>) {
            switch (pos) {
                case alignment::centre:
                    return (parent - child) / 2;
                case alignment::end:
                    return parent - child;
                case alignment::start:
                default:
                    return 0;
            }
        } else {
            return pos;
        }
    }, position);
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
