// Character.cpp

#include "Character.h"
#include "../engine/Game.h"   // TILE_SIZE

#include <cmath>

void character_place(Character& character, int grid_x, int grid_y) {

    character.grid_x = grid_x;
    character.grid_y = grid_y;

    character.x = grid_x * TILE_SIZE;
    character.y = grid_y * TILE_SIZE;
}

void character_try_move(Character& character, int dx, int dy) {

    if (character.moving) return;

    character.grid_x += dx;
    character.grid_y += dy;
    character.moving = true;
}

void character_update(Character& character, float dt) {

    if (!character.moving) return;

    float target_x = character.grid_x * TILE_SIZE;
    float target_y = character.grid_y * TILE_SIZE;

    float step = character.move_speed * dt;

    float dx = target_x - character.x;
    float dy = target_y - character.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist <= step) {
        character.x = target_x;
        character.y = target_y;
        character.moving = false;
    }
    else {
        character.x += dx / dist * step;
        character.y += dy / dist * step;
    }
}