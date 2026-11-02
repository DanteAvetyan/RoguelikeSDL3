// Player.cpp

#include "Player.h"

#include <SDL3/SDL.h>

void player_handle_movement(Character& player) {

    const bool* keys = SDL_GetKeyboardState(nullptr);

    if      (keys[SDL_SCANCODE_W]) character_try_move(player,  0, -1);
    else if (keys[SDL_SCANCODE_S]) character_try_move(player,  0,  1);
    else if (keys[SDL_SCANCODE_A]) character_try_move(player, -1,  0);
    else if (keys[SDL_SCANCODE_D]) character_try_move(player,  1,  0);
}