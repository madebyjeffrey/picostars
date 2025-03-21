cmake_minimum_required(VERSION 3.30)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/support")

include(CopyResources)
include(CopyFramework)
include(CodeSign)

project(PicoStars)

set(CMAKE_CXX_STANDARD 23)

include_directories(./headers)

# Find SDL3, SDL3_image, and SDL3_ttf frameworks
find_library(SDL3_FRAMEWORK SDL3 PATHS /Library/Frameworks NO_DEFAULT_PATH)
find_library(SDL3_IMAGE_FRAMEWORK SDL3_image PATHS /Library/Frameworks NO_DEFAULT_PATH)
find_library(SDL3_TTF_FRAMEWORK SDL3_ttf PATHS /Library/Frameworks NO_DEFAULT_PATH)
find_library(WEBP_FRAMEWORK webp PATHS /Library/Frameworks NO_DEFAULT_PATH)
find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)

message(STATUS "SDL3: ${SDL3_FRAMEWORK}")
message(STATUS "SDL3_image: ${SDL3_IMAGE_FRAMEWORK}")
message(STATUS "SDL3_ttf: ${SDL3_TTF_FRAMEWORK}")
message(STATUS "webp: ${WEBP_FRAMEWORK}")
message(STATUS "CoreFoundation: ${CORE_FOUNDATION_FRAMEWORK}")

# Add the executable
add_executable(PicoStars
        src/main.cpp
        src/assets.cpp
        src/app_constants.cpp
        src/app_sdl_lifecycle.cpp
        headers/app_state.h
        headers/app_constants.h
        headers/lifecycle.h
        headers/assets.h
        headers/error.h
        headers/image.h
        headers/alignment.h
        headers/scene_nodes.h
        src/scene_nodes.cpp
        headers/title_scene.h
        src/title_scene.cpp
)

set_target_properties(PicoStars PROPERTIES INSTALL_RPATH
        "@executable_path/../Frameworks")
set_target_properties(PicoStars PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)

# Link the frameworks
target_link_libraries(PicoStars
        ${SDL3_FRAMEWORK}
        ${SDL3_IMAGE_FRAMEWORK}
        ${SDL3_TTF_FRAMEWORK}
        ${WEBP_FRAMEWORK}
        ${CORE_FOUNDATION_FRAMEWORK}
)

# Set the output directory for the app bundle
set_target_properties(PicoStars PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist
)

copy_framework(SDL3 PicoStars)
copy_framework(SDL3_image PicoStars)
copy_framework(SDL3_ttf PicoStars)
copy_framework(webp PicoStars)

# Copy the AppIcon.icns to the app bundle
add_custom_command(TARGET PicoStars POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/AppIcon.icns
        ${CMAKE_BINARY_DIR}/PicoStars.app/Contents/Resources/AppIcon.icns
)
set(RESOURCE_PATH ${CMAKE_SOURCE_DIR}/resources)
copy_resources(${RESOURCE_PATH} "AppIcon.icns" PicoStars PicoStars)
copy_asset(${RESOURCE_PATH} "PicoStars.png" PicoStars PicoStars)
copy_asset(${RESOURCE_PATH} "Arya-Bold.ttf" PicoStars PicoStars)
copy_asset(${RESOURCE_PATH} "Arya-Regular.ttf" PicoStars PicoStars)
copy_asset(${RESOURCE_PATH} "ByteBounce.ttf" PicoStars PicoStars)
copy_asset_dir(${RESOURCE_PATH} "title" PicoStars PicoStars)

message(STATUS "Output Directory: ${CMAKE_BINARY_DIR}/PicoStars.app/Contents/MacOS")
message(STATUS "Info.plist Path: ${CMAKE_SOURCE_DIR}/Info.plist")
message(STATUS "SDL3 Framework Path: ${SDL3_FRAMEWORK}")
message(STATUS "SDL3_image Framework Path: ${SDL3_IMAGE_FRAMEWORK}")
message(STATUS "SDL3_ttf Framework Path: ${SDL3_TTF_FRAMEWORK}")

code_sign_framework("Apple Development" PicoStars PicoStars SDL3)
code_sign_framework("Apple Development" PicoStars PicoStars SDL3_image)
code_sign_framework("Apple Development" PicoStars PicoStars SDL3_ttf)
code_sign_framework("Apple Development" PicoStars PicoStars webp)
code_sign("Apple Development" PicoStars PicoStars ${CMAKE_SOURCE_DIR}/picostars.entitlements)
