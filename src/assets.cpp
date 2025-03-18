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

#include <filesystem>
#include <optional>
#include <iostream>
#include <fstream>
#include <span>

#include <string.h>

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
    if (!CFURLGetFileSystemRepresentation(bundleURL, true, reinterpret_cast<UInt8*>(path), PATH_MAX)) {
        std::cerr << "Failed to convert URL to file system representation" << std::endl;
        return std::nullopt;
    }
    
    CFRelease(bundleURL);
    
    fs::path bundlePath(path, reinterpret_cast<char*>(memchr(path, 0, PATH_MAX)));
    
    CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(bundleRef);
    
    if (resourceURL == nullptr) {
        std::cerr << "Failed to get resource directory url." << std::endl;
        return std::nullopt;
    }
    
    if (!CFURLGetFileSystemRepresentation(resourceURL, false, reinterpret_cast<UInt8*>(path), PATH_MAX)) {
        std::cerr << "Failed to convert resource URL to file system representation" << std::endl;
        return std::nullopt;
    }
    
    fs::path resourcePath(path, reinterpret_cast<char*>(memchr(path, 0, PATH_MAX)));
    
    return bundlePath / resourcePath;
}
#endif
#endif

auto get_asset_path(std::string &name) -> std::optional<fs::path> {
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

auto get_asset(std::string &name) -> std::optional<std::span<uint8_t>> {
    auto path = get_asset_path(name);
    
    if (!path.has_value()) {
        std::cerr << "get_asset: asset \"" << name << "\" does not exist.";
        
        return std::nullopt;
    }
    
    if (std::ifstream is{path.value(), std::ios::binary | std::ios::ate}) {
        size_t size = is.tellg();
        
        uint8_t *s = new uint8_t[size];
        
        is.seekg(0, std::ios::beg);
        
        if (is.read(reinterpret_cast<char*>(s), size)) {
            return std::span{s, size};
        }
        
        std::cerr << "get_asset: Unable to read from \"" << name << "\"" << std::endl;
    }
    
    return std::nullopt;
}

