//
// Created by Jeffrey Drake on 2025-03-23.
//

#ifndef NODE_H
#define NODE_H

#include <utility>

#include "Utility.h"

class Node {
	std::tuple<Alignment, Alignment> origin = {Alignment::start, Alignment::start};
    std::tuple<Offset, Offset> offset = {0_px, 0_px};

    public:
    Node() = default;

    Node &withAlignment(Alignment horizontal, Alignment vertical) {
        origin = {horizontal, vertical};
        return *this;
    }

    Node &withOffset(Offset horizontal, Offset vertical) {
        offset = {horizontal, vertical};
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