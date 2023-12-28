cmake_minimum_required(VERSION 3.27)
project(t3)

set(CMAKE_CXX_STANDARD 17)

# Set the path to SDL2 installation directory
set(SDL2_INSTALL_DIR "${CMAKE_SOURCE_DIR}/SDL_Build")
set(T3_FRAMEWORK_DIR "${CMAKE_SOURCE_DIR}/framework")


# Include SDL2 headers from the installation directory
include_directories(${SDL2_INSTALL_DIR}/include/SDL2)
include_directories(${T3_FRAMEWORK_DIR})


# Add the source files to the project
add_executable(t3 main.cpp
        framework/config/game-config.h
        main.h
        framework/helper/logging.h
        framework/helper/logging.cpp)

# Link SDL2 library
target_link_libraries(t3 ${SDL2_INSTALL_DIR}/lib/libSDL2.so)