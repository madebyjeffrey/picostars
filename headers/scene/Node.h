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

    public:
    Node() = default;

    Node &WithContentAlignment(Alignment horizontal, Alignment vertical) {
        content_alignment_ = {horizontal, vertical};
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