
// Renderer.h

#pragma once

#include "Game.h"

bool loadTexture(SDL_Renderer* renderer);

void draw_sprite(
    SDL_Renderer* renderer,
    SDL_Texture* texture,
    const Character& character,
    const Camera& camera
);

void draw_filled_oval(
    SDL_Renderer* renderer,
    int center_x,
    int center_y,
    int radius_x,
    int radius_y
);

void grid_to_coordinates(
    Character& character,
    int grid_x,
    int grid_y
);

void setCamera(
    const Character& player,
    Camera& camera
);}