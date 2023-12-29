cmake_minimum_required(VERSION 3.27)
project(t3)

set(CMAKE_CXX_STANDARD 17)

# Set the path to SDL2 installation directory
set(SDL2_INSTALL_DIR "${PROJECT_SOURCE_DIR}/SDL_Build")
set(SDL2_IMAGE_EXTENSION_DIR "${PROJECT_SOURCE_DIR}/SDL_image-release-2.8.1/")
set(SDL2_IMAGE_EXTENSION_BUILD_DIR "${PROJECT_SOURCE_DIR}/SDL_Image/Build")
set(T3_FRAMEWORK_DIR "${PROJECT_SOURCE_DIR}/framework")


# Include SDL2 headers from the installation directory
include_directories(${SDL2_INSTALL_DIR}/include/SDL2)
include_directories(${SDL2_IMAGE_EXTENSION_DIR}/include)
include_directories(${T3_FRAMEWORK_DIR})

find_library(SDL2_LIBRARY NAMES SDL2 HINTS "${SDL2_LIBRARY_DIR}/.libs")
find_library(SDL2_IMAGE_LIBRARY NAMES SDL2 HINTS "${SDL2_IMAGE_EXTENSION_BUILD_DIR}/.libs")

# Add the source files to the project
add_executable(t3 main.cpp
        framework/config/game-config.h
        main.h
        framework/helper/logging.h
        framework/helper/logging.cpp)

# Link SDL2 library
target_link_libraries(t3 PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})