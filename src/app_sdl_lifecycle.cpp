//
// Created by Jeffrey Drake on 2025-03-19.
//

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_error.h>

#include <cmath>
#include <iostream>

#include "app_state.h"

#include "lifecycle.h"

static const struct {
    const char *key;
    const char *value;
} extended_metadata[] =
{
    {SDL_PROP_APP_METADATA_URL_STRING, "https://github.com/madebyjeffrey/picostars"},
    {SDL_PROP_APP_METADATA_CREATOR_STRING, "Jeffrey Drake"},
    {SDL_PROP_APP_METADATA_COPYRIGHT_STRING, "© 2025 By Jeffrey Drake. All rights reserved."},
    {SDL_PROP_APP_METADATA_TYPE_STRING, "game"}
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    size_t i;

    if (!SDL_SetAppMetadata("PicoStars", "0.1", "ca.ideaplex.picostars")) {
        return SDL_APP_FAILURE;
    }

    for (i = 0; i < SDL_arraysize(extended_metadata); i++) {
        if (!SDL_SetAppMetadataProperty(extended_metadata[i].key, extended_metadata[i].value)) {
            return SDL_APP_FAILURE;
        }
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_APP_FAILURE;
    }

    try {
        AppState *as = new AppState;

        *appstate = as;

        switch (auto result = setup(*as)) {
            case Status::Continue:
                return SDL_APP_CONTINUE;
            case Status::Failure:
                return SDL_APP_FAILURE;
            case Status::Success:
                return SDL_APP_SUCCESS;
        }
    } catch (std::bad_alloc &e) {
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState *as = static_cast<AppState *>(appstate);
    const Uint64 now = SDL_GetTicks();
    const Uint64 last_step = as->last_step;
    const Uint64 delta = now - last_step;

    auto result = loop(*as, delta);

    as->last_step = now;

    switch (result) {
        case Status::Continue:
            return SDL_APP_CONTINUE;
        case Status::Failure:
            return SDL_APP_FAILURE;
        case Status::Success:
            return SDL_APP_SUCCESS;
    }
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    //    SnakeContext *ctx = &((AppState *)appstate)->snake_ctx;
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            //return handle_key_event_(ctx, event->key.scancode);
            return SDL_APP_CONTINUE;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    if (appstate != nullptr) {
        auto *as = static_cast<AppState *>(appstate);
        // SDL_DestroyRenderer(as->renderer);
        // SDL_DestroyWindow(as->window);
        delete as;
    }
}
