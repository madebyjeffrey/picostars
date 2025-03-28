//
// Created by Jeffrey Drake on 2025-03-24.
//

#ifndef NODECONTENT_H
#define NODECONTENT_H

#include <SDL3/SDL.h>

#include "Types.h"

class NodeContent {
public:
    virtual ~NodeContent() = default;

    [[nodiscard]] virtual auto GetSize() const -> Size<int> = 0;

    virtual auto Render(std::unique_ptr<SDL_Renderer> const &renderer, const Rect<int> &destination) const -> void = 0;
};

class ImageContent : public NodeContent {
    std::unique_ptr<SDL_Texture> texture_;

public:
    [[nodiscard]] auto GetSize() const -> Size<int> override {
        float w, h;

        SDL_GetTextureSize(texture_.get(), &w, &h);

        double dw = w, dh = h;

        return Size<int>{static_cast<int>(dw), static_cast<int>(dh)};
    }

    auto Render(std::unique_ptr<SDL_Renderer> const &renderer, const Rect<int> &destination) const -> void override {
        auto dst = destination.asFRect();

        SDL_RenderTexture(renderer.get(), texture_.get(), nullptr, &dst);
    }
};


#endif //NODECONTENT_H
