// Renderer.h

#pragma once

#include "Game.h"

// Path is relative to the project root, e.g. "assets/....png"
SDL_Texture* load_texture(SDL_Renderer* renderer, const char* relative_path);

void draw_character(
    SDL_Renderer* renderer,
    const Character& character,
    const Camera& camera
);

void draw_grid(
    SDL_Renderer* renderer,
    const Camera& camera
);

void draw_filled_oval(
    SDL_Renderer* renderer,
    int center_x,
    int center_y,
    int radius_x,
    int radius_y
);

void camera_follow(
    Camera& camera,
    const Character& target
);