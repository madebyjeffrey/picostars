//
//  textures.cpp
//  picostars
//
//  Created by Jeffrey Drake on 2025-03-13.
//

#include <SDL3/SDL.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_error.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <optional>
#include <iostream>

#include "loader.h"
#include "assets.h"

auto load_texture_asset(SDL_Renderer *renderer, std::string name) -> std::optional<SDL_Texture *> {
    auto mpath = get_asset_path(name);
    
    if (!mpath.has_value()) {
        std::cerr << "load_texture_asset: unable to get path to asset " << name << std::endl;
    }
    
    auto path = mpath.value();
    
    auto s = get_asset(name);
    
    if (!s.has_value()) {
        std::cerr << "load_texture_asset: unable to load " << name << std::endl;
        return std::nullopt;
    }
    
    auto data = s.value();
    
    SDL_IOStream *io = SDL_IOFromConstMem(data.data(), data.size_bytes());
    
    if (io == nullptr) {
        std::cerr << "load_texture_asset: SDL error: " << SDL_GetError() << std::endl;
        return std::nullopt;
    }
    
    SDL_Texture *texture = IMG_LoadTextureTyped_IO(renderer, io, true, path.extension().c_str());
    
    if (texture == nullptr) {
        std::cerr << "load_texture_asset: SDL error: " << SDL_GetError() << std::endl;
        return std::nullopt;
    }
    
    return texture;
}

auto load_font_asset(std::string name, float ptSize) -> std::optional<TTF_Font *> {
    auto mpath = get_asset_path(name);
    
    if (!mpath.has_value()) {
        std::cerr << "load_font_asset: unable to get path to asset " << name << std::endl;
    }
    
    auto path = mpath.value();
    
    auto s = get_asset(name);
    
    if (!s.has_value()) {
        std::cerr << "load_font_asset: unable to load " << name << std::endl;
        return std::nullopt;
    }
    
    auto data = s.value();
    
    SDL_IOStream *io = SDL_IOFromConstMem(data.data(), data.size_bytes());
    
    if (io == nullptr) {
        std::cerr << "load_font_asset: SDL error: " << SDL_GetError() << std::endl;
        return std::nullopt;
    }
    
    TTF_Font *font = TTF_OpenFontIO(io, true, ptSize);
    
    if (!font) {
        std::cerr << "Couldn't open font: " << SDL_GetError() << std::endl;
        return std::nullopt;
    }
    
    return font;
}



