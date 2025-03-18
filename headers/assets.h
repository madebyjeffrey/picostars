//
//  file-path.h
//  picostars
//
//  Created by Jeffrey Drake on 2025-03-12.
//

#ifndef FILE_PATH_H
#define FILE_PATH_H

#include <filesystem>
#include <optional>
#include <span>

namespace fs = std::filesystem;

auto get_resource_path() -> std::optional<fs::path>;
auto get_asset(std::string &name) -> std::optional<std::span<uint8_t>>;
auto get_asset_path(std::string &name) -> std::optional<fs::path>;

#endif
