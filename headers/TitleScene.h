//
// Created by Jeffrey Drake on 2025-03-21.
//

#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <vector>

#include "scene_nodes.h"
#include "scene/Scene.h"

class TitleScene : public Scene {
public:
    auto Setup(const Rect<int> &container, const std::unique_ptr<SDL_Renderer> &renderer) -> void override {
    }

    auto Loop(const Rect<int> &container, const std::unique_ptr<SDL_Renderer> &renderer) const -> void override;
};

#endif //TITLE_SCENE_H
