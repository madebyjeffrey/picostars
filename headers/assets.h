#ifndef FILE_PATH_H
#define FILE_PATH_H

#include <filesystem>
#include <optional>
#include <span>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace fs = std::filesystem;

class asset {
    std::span<uint8_t> data;

public:
    explicit asset(std::span<uint8_t> data) : data{data} {
    }

    [[nodiscard]] auto as_texture(const std::shared_ptr<SDL_Renderer> &renderer) const -> std::shared_ptr<SDL_Texture>;

    [[nodiscard]] auto as_font(float ptSize) const -> std::shared_ptr<TTF_Font>;
};


auto get_resource_path() -> std::optional<fs::path>;

auto get_asset_path(std::string name) -> std::optional<fs::path>;

auto load_asset(std::string name) -> asset;

#endif
