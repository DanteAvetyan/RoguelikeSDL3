// Input.cpp

#include <SDL3/SDL.h>
#include "Input.h"
#include "Game.h"

void users_ui_input(const SDL_Event& event) {

    if (event.type != SDL_EVENT_KEY_DOWN) return;

    switch (event.key.key) {
        case SDLK_Q:
            game.state = GameState::Quit;
            break;

        case SDLK_M:
            game.state = GameState::MainMenu;
            break;
    }
}

void users_utility_input(const SDL_Event& event) {

    if (event.type == SDL_EVENT_KEY_DOWN &&
        event.key.key == SDLK_I) {

        game.inventory.torch = !game.inventory.torch;
        }
}