
// Game.cpp


#include "Game.h"
#include "Renderer.h"
#include "Input.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>

Game game;

bool initialize_game() {

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "SDL initialization failed: "
                  << SDL_GetError() << '\n';
        return false;
    }

    game.window = SDL_CreateWindow(
        WINDOW_TITLE,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (!game.window) {
        std::cerr << "Window creation failed: "
                  << SDL_GetError() << '\n';
        SDL_Quit();
        return false;
    }

    game.renderer = SDL_CreateRenderer(game.window, nullptr);

    if (!game.renderer) {
        std::cerr << "Renderer creation failed: "
                  << SDL_GetError() << '\n';

        SDL_DestroyWindow(game.window);
        SDL_Quit();
        return false;
    }

    if (!loadTexture(game.renderer)) {
        SDL_DestroyRenderer(game.renderer);
        SDL_DestroyWindow(game.window);
        SDL_Quit();
        return false;
    }

    SDL_SetRenderDrawBlendMode(
        game.renderer,
        SDL_BLENDMODE_BLEND
    );

    grid_to_coordinates(game.player, 2, 1);
    setCamera(game.player, game.camera);

    return true;
}


void game_loop() {

    SDL_FRect rect = {
        (WINDOW_WIDTH - 800.0f) / 2.0f,
        (WINDOW_HEIGHT - 800.0f) / 2.0f,
        800.0f,
        800.0f
    };

    while (game.running) {

        user_specific_key_input();

        SDL_SetRenderDrawColor(
            game.renderer,
            20, 20, 30, 255
        );

        SDL_RenderClear(game.renderer);

        // Invisible square
        SDL_SetRenderDrawColor(
            game.renderer,
            0, 0, 0, 0
        );

        SDL_RenderFillRect(game.renderer, &rect);

        // Torchlight
        if (game.inventory.torch) {

            SDL_SetRenderDrawColor(
                game.renderer,
                255, 255, 255, 80
            );

            draw_filled_oval(
                game.renderer,
                WINDOW_WIDTH / 2,
                WINDOW_HEIGHT / 2 + 20,
                50,
                25
            );
        }

        // Character
        draw_sprite(
            game.renderer,
            game.character_texture,
            game.player,
            game.camera
        );

        SDL_RenderPresent(game.renderer);
    }
}

void shutdown_game() {

    if (game.character_texture) {
        SDL_DestroyTexture(game.character_texture);
    }

    if (game.renderer) {
        SDL_DestroyRenderer(game.renderer);
    }

    if (game.window) {
        SDL_DestroyWindow(game.window);
    }

    SDL_Quit();
}