//
// Created by Jeffrey Drake on 2025-03-24.
//

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <SDL3/SDL.h>

#include "Node.h"
#include "Types.h"

class Scene {
protected:
    std::vector<Node> nodes;

public:
    virtual ~Scene() = default;

    virtual auto Setup(Rect<int> const &container, const std::unique_ptr<SDL_Renderer> &renderer) -> void = 0;

    virtual auto Loop(Rect<int> const &container, const std::unique_ptr<SDL_Renderer> &renderer) const -> void = 0;
};

#endif //SCENE_H
