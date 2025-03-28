//
// Created by Jeffrey Drake on 2025-03-23.
//

#ifndef NODE_H
#define NODE_H

#include <memory>
#include <utility>

#include "Types.h"
#include "LocationProvider.h"
#include "NodeContent.h"

class Node {
    std::unique_ptr<LocationProvider> location_provider_;
    std::unique_ptr<NodeContent> content_;
    std::pair<Alignment, Alignment> content_alignment_;
    int z_index_;
    std::string name_;

public:
    Node() = default;

    [[nodiscard]] LocationProvider &GetLocationProvider() const noexcept {
        return *location_provider_;
    }

    [[nodiscard]] NodeContent &GetContent() const noexcept {
        return *content_;
    }

    [[nodiscard]] const std::string &GetName() const noexcept {
        return name_;
    }

    [[nodiscard]] const std::pair<Alignment, Alignment> &GetContentAlignment() const noexcept {
        return content_alignment_;
    }

    [[nodiscard]] int GetZIndex() const noexcept {
        return z_index_;
    }

    Node &WithName(std::string name) {
        name_ = std::move(name);
        return *this;
    }

    Node &WithContentAlignment(Alignment horizontal, Alignment vertical) {
        content_alignment_ = {horizontal, vertical};
        return *this;
    }

    Node &WithZIndex(int z_index) {
        z_index_ = z_index;
        return *this;
    }

    Node &WithContent(std::unique_ptr<NodeContent> content) {
        content_ = std::move(content);
        return *this;
    }

    Node &WithContent(NodeContent &&content) {
        content_ = std::make_unique<NodeContent>(content);
        return *this;
    }

    Node &WithLocationProvider(std::unique_ptr<LocationProvider> location_provider) {
        location_provider_ = std::move(location_provider);
        return *this;
    }

    template<LocationProviderType T>
    Node &WithLocationProvider(T &&location_provider) {
        location_provider_.reset(new T(std::forward<T>(location_provider)));
        return *this;
    }

    auto Render(std::unique_ptr<SDL_Renderer> const &renderer, Rect<int> const &parent) const -> void {
        auto position = location_provider_->GetPosition(parent, content_->GetSize(), content_alignment_);
        Rect<int> destination = Rect<int>::make(position, content_->GetSize());
        content_->Render(renderer, destination);
    }
};

#endif //NODE_H

/*

general idea:
    generic node will contain content

eg.
    node()
    .content(image)
    .alignment(...)

This way they can go into a vector

 */
