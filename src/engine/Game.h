
// Game.h

#pragma once

#include <SDL3/SDL.h>

#define WINDOW_TITLE "My Roguelike"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TILE_SIZE 100

struct Character {
    float x = 0;
    float y = 0;

    float offset_x = 0;
    float offset_y = 0;

    int sprite_column = 0;
    int sprite_row = 0;
};

struct Inventory {
    bool torch = false;
};

struct Camera {
    float x = 0;
    float y = 0;

    float zoom = 3.0f;
};

struct Game {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* character_texture = nullptr;

    Character player;
    Camera camera;
    Inventory inventory;

    SDL_Event event;
    bool running = true;
};

// Declaration: the actual game object is defined in Game.cpp.
extern Game game;

bool initialize_game();
void game_loop();
void shutdown_game();

void user_specific_key_input();