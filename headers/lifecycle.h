//
// Created by Jeffrey Drake on 2025-03-19.
//

#ifndef LIFECYCLE_H
#define LIFECYCLE_H

#include "app_state.h"

enum class Status {
    Continue,
    Success,
    Failure
};

auto setup(AppState &app) -> Status;
auto loop(AppState const &app, Uint64 deltaTime) -> Status;

#endif //LIFECYCLE_H
