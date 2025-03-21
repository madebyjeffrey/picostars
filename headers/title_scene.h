//
// Created by Jeffrey Drake on 2025-03-21.
//

#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <vector>

#include "scene_nodes.h"

class title_scene {
public:
    std::vector<std::shared_ptr<scene_node> > nodes;

    title_scene(): nodes{} {
    }

    auto setup(rect container, const std::shared_ptr<SDL_Renderer> &renderer) -> void;

    auto loop(rect container, const std::shared_ptr<SDL_Renderer> &renderer) const -> void;
};

#endif //TITLE_SCENE_H
