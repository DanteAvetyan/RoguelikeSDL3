
// Input.cpp

#include <SDL3/SDL.h>
#include "Game.h"

void user_specific_key_input() {
    while (SDL_PollEvent(&game.event)) {

        if (game.event.type == SDL_EVENT_QUIT) {
            game.running = false;
        }

        if (game.event.type == SDL_EVENT_KEY_DOWN &&
            game.event.key.key == SDLK_Q) {

            game.running = false;

            }
        else if (game.event.type == SDL_EVENT_KEY_DOWN &&
                 game.event.key.key == SDLK_I) {

            game.inventory.torch = !game.inventory.torch;
                 }
    }
}