//
// Created by Jeffrey Drake on 2025-03-19.
//

#ifndef APP_STATE_H
#define APP_STATE_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "scene_nodes.h"
#include "TitleScene.h"

struct AppState {
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;
    std::shared_ptr<SDL_Texture> titleImage;
    std::shared_ptr<TTF_Font> displayFont;
    std::shared_ptr<SDL_Texture> titleText;
    // std::shared_ptr<SDL_Texture> largePlanet;
    title_scene titleScene;
    Uint64 last_step{};

    AppState() = default;
};

#endif //APP_STATE_H
