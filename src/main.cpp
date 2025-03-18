/* snake.c ... */

/*
 * Logic implementation of the Snake game. It is designed to efficiently
 * represent the state of the game in memory.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_error.h>

#include <math.h>

#include <string>
#include <filesystem>
#include <iostream>

#include "assets.h"
#include "loader.h"
#include "image.h"

#define STEP_RATE_IN_MILLISECONDS  125

const unsigned int BlockSize = 16;
const unsigned int WindowBlockWidth = 30 * 2;
const unsigned int WindowBlockHeight = 17 * 2;
const unsigned int WindowWidth = BlockSize * WindowBlockWidth;
const unsigned int WindowHeight = BlockSize * WindowBlockHeight;
const float baseFont = 6.0f;


typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *titleImage;
    TTF_Font *displayFont;
    Uint64 last_step;
} AppState;

int find_largest_scale(int cx, int cy, int w, int h) {
    int scale_w = w / cx;
    int scale_h = h / cy;
    return (scale_w < scale_h) ? scale_w : scale_h;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *as = (AppState *)appstate;
    const Uint64 now = SDL_GetTicks();
    SDL_FRect r;

    unsigned i;
    unsigned j;
    int ct;

    int w, h;

    SDL_GetRenderOutputSize(as->renderer, &w, &h);

    float cx, cy;

    SDL_GetTextureSize(as->titleImage, &cx, &cy);

    float scale = (float)find_largest_scale(floor(cx), floor(cy), floor(w), floor(h));

    SDL_SetRenderScale(as->renderer, scale, scale);

    int scaled_width = floor(cx) * scale;
    int scaled_height = floor(cy) * scale;

    int offset_x = (w - scaled_width) / (2 * scale);
    int offset_y = (h - scaled_height) / (2 * scale);

    SDL_FRect dst;

    dst.x = offset_x;
    dst.y = offset_y;
    dst.w = cx;
    dst.h = cy;

    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, 255);
    SDL_RenderClear(as->renderer);

    SDL_RenderTexture(as->renderer, as->titleImage, NULL, &dst);

    SDL_Color color = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    SDL_Color bg = { 0, 0, 0, SDL_ALPHA_OPAQUE };

    // going to need a base font size, then multiply it by the scale so it can be rendered,
    // also going to need to know the location of the current presentation
    TTF_SetFontSize(as->displayFont, baseFont * scale);
    SDL_Surface *text = TTF_RenderText_Solid(as->displayFont, "Hail Satan", 0, color);

    if (text) {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(as->renderer, text);
        SDL_DestroySurface(text);

        if (!texture) {
            std::cerr << "Could not create text, " << SDL_GetError() << std::endl;
        } else {
            SDL_FRect r {
                .x =  30,
                .y =  30
            };
            SDL_GetTextureSize(texture, &r.w, &r.h);
            SDL_RenderTexture(as->renderer, texture, nullptr, &r);
        }
    }


    SDL_RenderPresent(as->renderer);

    // run game logic if we're at or past the time to run it.
    // if we're _really_ behind the time to run it, run it
    // several times.
//    while ((now - as->last_step) >= STEP_RATE_IN_MILLISECONDS) {
//        snake_step(ctx);
//        as->last_step += STEP_RATE_IN_MILLISECONDS;
//    }

//    r.w = r.h = SNAKE_BLOCK_SIZE_IN_PIXELS;
//    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//    SDL_RenderClear(as->renderer);
//
    //SDL_SetRenderDrawColor(as->renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); /*head*/
//    set_rect_xy_(&r, ctx->head_xpos, ctx->head_ypos);
//    SDL_RenderFillRect(as->renderer, &r);
//    SDL_RenderPresent(as->renderer);
    return SDL_APP_CONTINUE;
}

static const struct
{
    const char *key;
    const char *value;
} extended_metadata[] =
{
    { SDL_PROP_APP_METADATA_URL_STRING, "https://github.com/madebyjeffrey/picostars" },
    { SDL_PROP_APP_METADATA_CREATOR_STRING, "Jeffrey Drake" },
    { SDL_PROP_APP_METADATA_COPYRIGHT_STRING, "© 2025 By Jeffrey Drake. All rights reserved." },
    { SDL_PROP_APP_METADATA_TYPE_STRING, "game" }
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
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

    AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
    if (!as) {
        return SDL_APP_FAILURE;
    }

    *appstate = as;

    if (!SDL_CreateWindowAndRenderer("PicoStars!", WindowWidth, WindowHeight, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE, &as->window, &as->renderer)) {
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        std::cerr << "Couldn't initialise SDL_ttf: " << SDL_GetError() << std::endl;
        return SDL_APP_FAILURE;
    }

    auto texture = load_texture_asset(as->renderer, "PicoStars.png");

    if (!texture.has_value()) {
        std::cerr << "AppInit: Cannot load title image." << std::endl;
        return SDL_APP_FAILURE;
    }

    as->titleImage = texture.value();

    auto font = load_font_asset("ByteBounce.ttf", baseFont);

    if (!font.has_value())
    {
        std::cerr << "AppInit: Couldn't load display font." << std::endl;
        return SDL_APP_FAILURE;
    }

    as->displayFont = font.value();

    as->last_step = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{

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

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    if (appstate != NULL) {
        AppState *as = (AppState *)appstate;
        SDL_DestroyRenderer(as->renderer);
        SDL_DestroyWindow(as->window);
        SDL_free(as);
    }
}

