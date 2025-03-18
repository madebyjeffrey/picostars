//
//  textures.h
//  picostars
//
//  Created by Jeffrey Drake on 2025-03-13.
//

#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL3/SDL.h>
#include <string>

auto load_texture_asset(SDL_Renderer *renderer, std::string name) -> std::optional<SDL_Texture *>;
auto load_font_asset(std::string name, float ptSize) -> std::optional<TTF_Font *>;

#endif
