// Game.h

#pragma once

#include "../entities/Character.h"

#include <SDL3/SDL.h>
#include <vector>

#define WINDOW_TITLE "My Roguelike"
#define TILE_SIZE 100
#define SPRITE_FRAME_SIZE 100


enum class GameState {
    MainMenu,
    Playing,
    Paused,
    Quit
};

struct Menu {
    int selected = 0;
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

    Character player;
    Character orc;
    std::vector<Character> enemies;

    Camera camera;
    Inventory inventory;

    GameState state = GameState::MainMenu;
    Menu menu;

    SDL_Event event;

    int screen_width = 0;
    int screen_height = 0;
};

// Declaration: the actual game object is defined in Game.cpp.
extern Game game;

bool initialize_game();
void game_loop();
void shutdown_game();