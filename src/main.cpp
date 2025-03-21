
#include <cmath>
#include <iostream>
#include <variant>

#include "app_constants.h"
#include "assets.h"
#include "lifecycle.h"
#include "error.h"

auto setup(AppState &app) -> Status {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (!SDL_CreateWindowAndRenderer("PicoStars!", base_window_width, base_window_height,
                                     SDL_WINDOW_RESIZABLE, &window,
                                     &renderer)) {
        return Status::Failure;
    }

    app.window = {window, SDL_DestroyWindow};
    app.renderer = {renderer, SDL_DestroyRenderer};

    auto scale = SDL_GetWindowDisplayScale(app.window.get());

    if (!TTF_Init()) {
        std::cerr << "Couldn't initialise SDL_ttf: " << SDL_GetError() << std::endl;
        return Status::Failure;
    }

    int w, h;

    SDL_GetRenderOutputSize(app.renderer.get(), &w, &h);

    std::cout << w << " x " << h << std::endl;

    rect windowRect{
        .x = 0,
        .y = 0,
        .w = w,
        .h = h
    };

    try {
        auto texture = load_asset("PicoStars.png").as_texture(app.renderer);

        app.titleImage = texture;

        auto font = load_asset("ByteBounce.ttf").as_font(base_font_size);

        app.displayFont = font;

        app.titleScene.setup(windowRect, app.renderer);

        app.last_step = SDL_GetTicks();

        return Status::Continue;
    } catch (Error &e) {
        std::cerr << e._description << std::endl;
        return Status::Failure;
    }
}


int find_largest_scale(const float cx, const float cy, const int w, const int h) {
    int scale_w = static_cast<int>(w / cx);
    int scale_h = static_cast<int>(h / cy);
    return (scale_w < scale_h) ? scale_w : scale_h;
}

auto loop(AppState const &app, Uint64 deltaTime) -> Status {
    SDL_FRect r;

    unsigned i;
    unsigned j;
    int ct;

    int w, h;

    SDL_GetRenderOutputSize(app.renderer.get(), &w, &h);

    std::cout << w << " x " << h << std::endl;

    rect windowRect{
        .x = 0,
        .y = 0,
        .w = w,
        .h = h
    };

    // float cx, cy;

    // SDL_GetTextureSize(app.largePlanet.get(), &cx, &cy);

    // auto scale = static_cast<float>(find_largest_scale(floor(cx), floor(cy), w, h));

    auto scale = SDL_GetWindowDisplayScale(app.window.get());
    // SDL_SetRenderScale(app.renderer, scale, scale);

    // int scaled_width = static_cast<int>(cx) * scale;
    // int scaled_height = static_cast<int>(trunc(cy)) * scale;

    // int offset_x = (w - scaled_width) / (2 * scale);
    // int offset_y = (h - scaled_height) / (2 * scale);


    // std::cout << cx << " / " << (w + cx) / 2 << std::endl;

    // dst.x = ((w + cx) / 2) * scale;
    // dst.y = (h - cy) * scale;
    // dst.w = cx * scale;
    // dst.h = cy * scale;

    SDL_SetRenderDrawColor(app.renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(app.renderer.get());

    // SDL_RenderTexture(app.renderer, app.titleImage.get(), nullptr, &dst);

    app.titleScene.loop(windowRect, app.renderer);

    // SDL_RenderTexture(app.renderer, app.largePlanet.get(), nullptr, &dst);

    SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};
    SDL_Color bg = {0, 0, 0, SDL_ALPHA_OPAQUE};

    // going to need a base font size, then multiply it by the scale so it can be rendered,
    // also going to need to know the location of the current presentation
    // TTF_SetFontSize(app.displayFont.get(), base_font_size * scale);
    // SDL_Surface *text = TTF_RenderText_Solid(app.displayFont.get(), "Some Text", 0, color);

    // if (text) {
    //     SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, text);
    //     SDL_DestroySurface(text);
    //
    //     if (!texture) {
    //         std::cerr << "Could not create text, " << SDL_GetError() << std::endl;
    //     } else {
    //         SDL_FRect r{
    //             .x = 30,
    //             .y = 30
    //         };
    //         SDL_GetTextureSize(texture, &r.w, &r.h);
    //         SDL_RenderTexture(app.renderer, texture, nullptr, &r);
    //     }
    // }


    SDL_RenderPresent(app.renderer.get());

    return Status::Continue;
}
