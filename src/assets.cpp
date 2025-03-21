//
//  file-path.cpp
//  picostars
//
//  Created by Jeffrey Drake on 2025-03-12.
//

#ifdef __APPLE__
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFStringEncodingExt.h>
#endif

#include <SDL3_image/SDL_image.h>

#include <filesystem>
#include <optional>
#include <iostream>
#include <fstream>
#include <span>
#include <cstring>

#include "error.h"
#include "assets.h"

namespace fs = std::filesystem;

#ifdef __APPLE__
#if TARGET_OS_MAC
auto get_resource_path() -> std::optional<fs::path> {
    CFBundleRef bundleRef = CFBundleGetMainBundle();

    if (bundleRef == nullptr) {
        std::cerr << "Cannot get main bundle." << std::endl;
        return std::nullopt;
    }

    CFURLRef bundleURL = CFBundleCopyBundleURL(bundleRef);

    if (bundleURL == nullptr) {
        std::cerr << "Cannot get main bundle url." << std::endl;
        return std::nullopt;
    }

    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(bundleURL, true, reinterpret_cast<UInt8 *>(path), PATH_MAX)) {
        std::cerr << "Failed to convert URL to file system representation" << std::endl;
        return std::nullopt;
    }

    CFRelease(bundleURL);

    fs::path bundlePath(path, reinterpret_cast<char *>(memchr(path, 0, PATH_MAX)));

    CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(bundleRef);

    if (resourceURL == nullptr) {
        std::cerr << "Failed to get resource directory url." << std::endl;
        return std::nullopt;
    }

    if (!CFURLGetFileSystemRepresentation(resourceURL, false, reinterpret_cast<UInt8 *>(path), PATH_MAX)) {
        std::cerr << "Failed to convert resource URL to file system representation" << std::endl;
        return std::nullopt;
    }

    fs::path resourcePath(path, reinterpret_cast<char *>(memchr(path, 0, PATH_MAX)));

    return bundlePath / resourcePath;
}
#endif
#endif

auto get_asset_path(std::string name) -> std::optional<fs::path> {
    auto basePath = get_resource_path();

    if (!basePath.has_value()) {
        std::cerr << "getAssetPath: Cannot get resource path" << std::endl;
        return std::nullopt;
    }

    auto pathToAsset = basePath.value() / "Assets" / name;

    if (fs::exists(pathToAsset)) {
        return pathToAsset;
    }

    std::cerr << "getAssetPath: Path to \"" << name << "\" does not exist." << std::endl;

    return std::nullopt;
}

auto load_asset(std::string name) -> asset {
    auto path = get_asset_path(name);

    if (!path.has_value()) {
        std::cerr << "load_asset: asset \"" << name << "\" does not exist.";

        throw error("Unable to load asset {}", name);
    }

    if (std::ifstream is{path.value(), std::ios::binary | std::ios::ate}) {
        size_t size = is.tellg();

        auto *s = new uint8_t[size];

        is.seekg(0, std::ios::beg);

        if (is.read(reinterpret_cast<char *>(s), static_cast<std::streamsize>(size))) {
            return asset{std::span{s, size}};
        }
    }

    std::cerr << "load_asset: Unable to read from \"" << name << "\"" << std::endl;

    throw error("Unable to load asset {}", name);
}

void delete_texture(SDL_Texture *texture) {
    SDL_DestroyTexture(texture);
}

auto asset::as_texture(const std::shared_ptr<SDL_Renderer> &renderer) const -> std::shared_ptr<SDL_Texture> {
    SDL_IOStream *io = SDL_IOFromConstMem(data.data(), data.size_bytes());

    if (io == nullptr) {
        std::cerr << "load_texture_asset: SDL error: " << SDL_GetError() << std::endl;
        throw error("Unable to load texture. Error {}", SDL_GetError());
    }

    SDL_Texture *texture = IMG_LoadTexture_IO(renderer.get(), io, true);

    if (texture == nullptr) {
        std::cerr << "load_texture_asset: SDL error: " << SDL_GetError() << std::endl;
        throw error("Unable to load texture. Error {}", SDL_GetError());
    }

    return std::shared_ptr<SDL_Texture>{texture, delete_texture};
}

void delete_font(TTF_Font *font) {
    TTF_CloseFont(font);
}

auto asset::as_font(float ptSize) const -> std::shared_ptr<TTF_Font> {
    SDL_IOStream *io = SDL_IOFromConstMem(data.data(), data.size_bytes());

    if (io == nullptr) {
        std::cerr << "as_font: SDL error: " << SDL_GetError() << std::endl;
        throw error("Unable to load font. Error {}", SDL_GetError());
    }

    TTF_Font *font = TTF_OpenFontIO(io, true, ptSize);

    if (!font) {
        std::cerr << "Couldn't open font: " << SDL_GetError() << std::endl;

        throw error("Unable to load font. Error {}", SDL_GetError());
    }

    return std::shared_ptr<TTF_Font>{font, delete_font};
}
