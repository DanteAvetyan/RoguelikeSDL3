cmake_minimum_required(VERSION 3.25)

project(RoguelikeSDL3 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Put the executable and SDL shared library together.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")

# Build SDL directly from our vendor directory.
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

# Our game executable.
add_executable(RoguelikeSDL3
        src/main.cpp
        src/engine/Game.cpp
        src/engine/Input.cpp
        src/engine/Renderer.cpp
        src/engine/Game.h
        src/engine/Input.h
        src/main.h
        src/engine/Menu.h
        src/engine/Menu.cpp
        src/entities/Player.h
        src/entities/Player.cpp
        src/entities/Character.h
        src/entities/Character.cpp
        src/entities/Enemies.h
        src/entities/Enemies.cpp
)

# Link SDL3 to our game.
target_link_libraries(RoguelikeSDL3 PRIVATE SDL3::SDL3)