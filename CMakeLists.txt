cmake_minimum_required(VERSION 3.27)
project(t3)

set(CMAKE_CXX_STANDARD 17)

# Set the path to SDL2 installation directory
set(T3_FRAMEWORK_DIR "${PROJECT_SOURCE_DIR}/framework")

# Include SDL2 headers from the installation directory
include_directories(${T3_FRAMEWORK_DIR})
include_directories(${PROJECT_SOURCE_DIR})

# Find SDL2 libraries
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

add_library(t3-framework
    framework/config/game-config.h
    framework/helper/logging.h
    framework/helper/logging.cpp
    framework/library/data_structures/abstract/stack.h 
    framework/library/data_structures/abstract/linked_list.h
    framework/library/data_structures/abstract/linked_list.cpp
    framework/library/data_structures/abstract/node.h
    framework/library/data_structures/abstract/node.cpp
    framework/helper/memory.h
    framework/library/data_structures/abstract/queue.h
    framework/library/data_structures/abstract/queue.cpp
    framework/library/data_structures/abstract/stack.cpp
    framework/library/data_structures/abstract/list.cpp
    framework/library/data_structures/abstract/list.h
    framework/library/ecs/entity.cpp
    framework/library/ecs/entity.h
    framework/library/ecs/component.cpp
    framework/library/ecs/component.h 
    framework/components/position.h
    framework/components/position.h
    framework/components/position.cpp
    framework/components/scene.h
    framework/components/scene.cpp
)

# Add the source files to the project
add_executable(t3 main.cpp
    main.h
    project/example-project-1/mushroom.h
    project/example-project-1/main_entity.h
)

# Link SDL2 and SDL_image libraries using CMake targets
target_link_libraries(
    t3-framework
    PUBLIC
    # SDL2
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    # SDL2 Image
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)

target_link_libraries(
    t3
    PRIVATE
    t3-framework
)