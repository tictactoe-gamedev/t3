cmake_minimum_required(VERSION 3.27)
project(t3)

set(CMAKE_CXX_STANDARD 17)

# Set the path to SDL2 installation directory
set(SDL2_INSTALL_DIR "${PROJECT_SOURCE_DIR}/SDL_Build")
set(SDL2_IMAGE_EXTENSION_BUILD_DIR "${PROJECT_SOURCE_DIR}/SDL_Image_Build")
set(T3_FRAMEWORK_DIR "${PROJECT_SOURCE_DIR}/framework")

# Include SDL2 headers from the installation directory
include_directories(${SDL2_INSTALL_DIR}/include/SDL2)
include_directories(${SDL2_IMAGE_EXTENSION_BUILD_DIR}/install/include/SDL2)
include_directories(${T3_FRAMEWORK_DIR})
include_directories(${PROJECT_SOURCE_DIR})

# Find SDL2 libraries
find_library(SDL2_LIBRARY NAMES SDL2 HINTS "${SDL2_INSTALL_DIR}/lib")
find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image HINTS "${SDL2_IMAGE_EXTENSION_BUILD_DIR}/.libs")

# Add the source files to the project
add_executable(t3 main.cpp
        framework/config/game-config.h
        main.h
        framework/helper/logging.h
        framework/helper/logging.cpp
        framework/library/data_structures/stack.h 
        framework/library/data_structures/linked_list.h
        framework/library/data_structures/linked_list.cpp
        framework/library/data_structures/node.h
        framework/library/data_structures/node.cpp
        framework/helper/memory.h
        framework/library/data_structures/queue.h
        framework/library/data_structures/queue.cpp
        framework/library/data_structures/stack.cpp
        framework/library/data_structures/list.cpp
        framework/library/data_structures/list.h
        framework/library/ecs/entity.cpp
        framework/library/ecs/entity.h
        framework/library/ecs/component.cpp
        framework/library/ecs/component.h
        framework/helper/variadic_macros.h
        framework/components/position.h
        framework/components/position.h
        framework/components/position.cpp
        project/example-project-1/mushroom.h
        project/example-project-1/main_entity.h
        framework/components/scene.h
        framework/components/scene.cpp)

# Link SDL2 and SDL_image libraries with full paths
target_link_libraries(t3 PRIVATE ${SDL2_INSTALL_DIR}/lib/libSDL2.so)
target_link_libraries(t3 PRIVATE ${SDL2_IMAGE_EXTENSION_BUILD_DIR}/install/lib/libSDL2_image.so)
