//
//  image.h
//  picostars
//
//  Created by Jeffrey Drake on 2025-03-13.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include "loader.h"
#include "error.h"

class ImageAsset {
private:
    std::unique_ptr<SDL_Texture*> _texture;
    
public:
    ImageAsset(SDL_Renderer *renderer, std::string asset): _texture(nullptr) {
        auto maybe_asset = load_texture_asset(renderer, asset);
        
        if (maybe_asset.has_value()) {
//            _texture = std::make_unique(maybe_asset.value());
        } else {
            throw make_error("Cannot load asset {}", asset);
        }
    }
};

#endif
