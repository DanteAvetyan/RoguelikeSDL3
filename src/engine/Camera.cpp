

// Camera.cpp

#include "Camera.h"

void camera_follow(
    const Character& target
) {

    float center_x = target.x + target.offset_x + TILE_SIZE / 2.0f;
    float center_y = target.y + target.offset_y + TILE_SIZE / 2.0f;

    game.camera.x = center_x - game.screen_width / (2.0f * game.camera.zoom);
    game.camera.y = center_y - game.screen_height / (2.0f * game.camera.zoom);
}