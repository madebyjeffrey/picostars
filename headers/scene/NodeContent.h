//
// Created by Jeffrey Drake on 2025-03-24.
//

#ifndef NODECONTENT_H
#define NODECONTENT_H

#include "Types.h"

class NodeContent {
public:
    virtual ~NodeContent() = default;

    [[nodiscard]] virtual auto GetSize() const -> Size<int> = 0;
};



#endif //NODECONTENT_H
