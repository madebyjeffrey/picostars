//
// Created by Jeffrey Drake on 2025-03-23.
//

#ifndef NODE_H
#define NODE_H

class NodeContent {
public:
    virtual ~node() = default;

    AlignmentOffset2D location;
    float scale;

    [[nodiscard]] virtual auto get_size() const -> size = 0;

    [[nodiscard]] auto resolve_location(rect parent) const -> rect;

    virtual auto render(const std::shared_ptr<SDL_Renderer> &renderer, rect parent) -> void = 0;

protected:
    scene_node(AlignmentOffset2D location, float scale) : location{location}, scale{scale} {
    }
};

class Node {
};

#endif //NODE_H
