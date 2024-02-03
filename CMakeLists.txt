cmake_minimum_required(VERSION 3.27)
project(t3 C)

set(CMAKE_C_STANDARD 90)

set(T3_FRAMEWORK_DIR "${PROJECT_SOURCE_DIR}/core")

# Set the path to SDL2 installation directory
set(SDL2_INSTALL_DIR "${PROJECT_SOURCE_DIR}/SDL_Build")
set(SDL2_IMAGE_EXTENSION_BUILD_DIR "${PROJECT_SOURCE_DIR}/SDL_Image_Build")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${T3_FRAMEWORK_DIR})

# Include SDL2 headers from the installation directory
include_directories(${SDL2_INSTALL_DIR}/include/SDL2)
include_directories(${SDL2_IMAGE_EXTENSION_BUILD_DIR}/install/include/SDL2)
include_directories(${SDL2_IMAGE_EXTENSION_BUILD_DIR}/include/SDL2)

# Find SDL2 libraries
if (WIN32)
    # Windows-specific settings
    find_library(SDL2_LIBRARY NAMES SDL2 HINTS "${SDL2_INSTALL_DIR}/lib")
    find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image HINTS "${SDL2_IMAGE_EXTENSION_BUILD_DIR}/lib/SDL2")
else ()
    # Linux-specific settings
    find_library(SDL2_LIBRARY NAMES SDL2 HINTS "${SDL2_INSTALL_DIR}/lib")
    find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image HINTS "${SDL2_IMAGE_EXTENSION_BUILD_DIR}/.libs")
endif ()

# Add the source files to the project
add_executable(t3 main.c
        core/config-project.h
        core/t3-types.h
        core/globals.h
        core/helpers.h
        core/source/helpers/logging.c
        core/source/adt/linked_list.c
        core/abstract-data-types.h
        core/source/adt/node.c
        core/source/adt/list.c
        core/source/adt/queue.c
        core/source/adt/stack.c
        core/source/helpers/randomisation.c
        core/ecs.h
        core/source/ecs/position.c
        core/source/ecs/entity.c
        project-root/start.c
        core/source/globals.c
        core/source/ecs/component.c
        core/source/ecs/scene.c
        core/source/ecs/game-loop.c
)

# Link SDL2 and SDL_image libraries with full paths
if (WIN32)
    target_link_libraries(t3 PRIVATE ${SDL2_INSTALL_DIR}/bin/SDL2.dll -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows)
    target_link_libraries(t3 PRIVATE ${SDL2_IMAGE_EXTENSION_BUILD_DIR}/bin/SDL2_image.dll -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows)
else ()
    target_link_libraries(t3 PRIVATE ${SDL2_INSTALL_DIR}/lib/libSDL2.so)
    target_link_libraries(t3 PRIVATE ${SDL2_IMAGE_EXTENSION_BUILD_DIR}/install/lib/libSDL2_image.so)
endif ()