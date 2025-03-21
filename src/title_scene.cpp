//
// Created by Jeffrey Drake on 2025-03-21.
//

#include "title_scene.h"
#include "scene_nodes.h"
#include "assets.h"

auto title_scene::setup(rect container, const std::shared_ptr<SDL_Renderer> &renderer) -> void {
    auto largePlanet = load_asset("title/LargePlanet.webp").as_texture(renderer);
    auto largePlanetNode = make_image_node(largePlanet, {alignment::centre, alignment::end}, 1.0f);

    nodes.push_back(largePlanetNode);
}

auto title_scene::loop(rect container, const std::shared_ptr<SDL_Renderer> &renderer) const -> void {
    for (auto &node: nodes) {
        node->render(renderer, container);
    }
}
