//
// Created by Jeffrey Drake on 2025-03-21.
//

#ifndef SCENE_NODES_H
#define SCENE_NODES_H

#include <SDL3/SDL.h>
#include <memory>

#include "alignment.h"

class scene_node {
public:
    virtual ~scene_node() = default;

    position location;
    float scale;

    [[nodiscard]] virtual auto get_size() const -> size = 0;

    [[nodiscard]] auto resolve_location(rect parent) const -> rect;

    virtual auto render(const std::shared_ptr<SDL_Renderer> &renderer, rect parent) -> void = 0;

protected:
    scene_node(position location, float scale) : location{location}, scale{scale} {
    }
};

class image_node : public scene_node {
public:
    std::shared_ptr<SDL_Texture> texture;

    explicit image_node() : scene_node{{alignment::start, alignment::start}, 1.0f} {
    }

    image_node(std::shared_ptr<SDL_Texture> texture, position location, float scale)
        : scene_node{location, scale}, texture{std::move(texture)} {
    }

    [[nodiscard]] auto get_size() const -> size override;

    auto render(const std::shared_ptr<SDL_Renderer> &renderer, rect parent) -> void override;
};

inline auto make_image_node(std::shared_ptr<SDL_Texture> &texture, position location,
                            float scale) -> std::shared_ptr<image_node> {
    return std::make_shared<image_node>(std::move(texture), location, scale);
}

#endif //SCENE_NODES_H
