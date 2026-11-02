// Character.h

#pragma once

#include <SDL3/SDL.h>

struct Character {
    // Drawn position in world pixels (slides smoothly)
    float x = 0;
    float y = 0;

    float offset_x = 0;
    float offset_y = 0;

    // Logical tile position (game rules use this)
    int grid_x = 0;
    int grid_y = 0;

    // Sprite
    SDL_Texture* texture = nullptr;
    int sprite_column = 0;
    int sprite_row = 0;

    // Movement
    bool moving = false;
    float move_speed = 300.0f;
};

// Teleport to a tile instantly (spawning)
void character_place(Character& character, int grid_x, int grid_y);

// Start walking one tile; ignored while already moving
void character_try_move(Character& character, int dx, int dy);

// Slide toward the target tile
void character_update(Character& character, float dt);