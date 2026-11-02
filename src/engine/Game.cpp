// Game.cpp

#include "Game.h"
#include "Renderer.h"
#include "Input.h"
#include "Menu.h"
#include "../entities/Character.h"
#include "../entities/Player.h"
#include "../entities/Enemies.h"

#include <SDL3/SDL.h>
#include <iostream>

Game game;

bool initialize_game() {

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "SDL initialization failed: "
                  << SDL_GetError() << '\n';
        return false;
    }

    const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
    int window_w = mode ? (int)(mode->w * 0.8f) : 1280;
    int window_h = mode ? (int)(mode->h * 0.8f) : 720;

    game.window = SDL_CreateWindow(
        WINDOW_TITLE,
        window_w,
        window_h,
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

    game.player.texture = load_texture(
        game.renderer,
        "assets/rpg_assets/Characters(100x100 split)/Soldier/Soldier/Soldier.png"
    );

    game.orc.texture = load_texture(
        game.renderer,
        "assets/rpg_assets/Characters(100x100 split)/Orc/Orc/Orc.png"
    );
    character_place(game.orc, 5, 3);
    game.enemies.push_back(game.orc);

    if (!game.player.texture) {
        SDL_DestroyRenderer(game.renderer);
        SDL_DestroyWindow(game.window);
        SDL_Quit();
        return false;
    }

    SDL_SetRenderDrawBlendMode(
        game.renderer,
        SDL_BLENDMODE_BLEND
    );

    SDL_GetRenderOutputSize(game.renderer, &game.screen_width, &game.screen_height);

    character_place(game.player, 2, 1);
    camera_follow(game.camera, game.player);

    return true;
}


static void playing_input(const SDL_Event& event) {
    users_ui_input(event);
    users_utility_input(event);
}

static void playing_update(float dt) {
    player_handle_movement(game.player);
    character_update(game.player, dt);
    for (Character& e : game.enemies)
        character_update(e, dt);
    camera_follow(game.camera, game.player);
}

static void playing_render() {

    draw_grid(game.renderer, game.camera);

    // Torchlight
    if (game.inventory.torch) {
        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 80);
        draw_filled_oval(
            game.renderer,
            game.screen_width / 2,
            game.screen_height / 2 + 20,
            50,
            25
        );
    }

    draw_character(game.renderer, game.player, game.camera);
    for (const Character& e : game.enemies)
        draw_character(game.renderer, e, game.camera);
}

void game_loop() {

    Uint64 last = SDL_GetTicksNS();

    while (game.state != GameState::Quit) {

        Uint64 now = SDL_GetTicksNS();
        float dt = (now - last) / 1'000'000'000.0f;
        last = now;

        SDL_GetRenderOutputSize(game.renderer, &game.screen_width, &game.screen_height);

        while (SDL_PollEvent(&game.event)) {
            if (game.event.type == SDL_EVENT_QUIT) {
                game.state = GameState::Quit;
            }

            switch (game.state) {
                case GameState::MainMenu: menu_input(game.event);    break;
                case GameState::Playing:  playing_input(game.event); break;
                default: break;
            }
        }

        if (game.state == GameState::Playing) {
            playing_update(dt);
        }

        SDL_SetRenderDrawColor(game.renderer, 20, 20, 30, 255);
        SDL_RenderClear(game.renderer);

        switch (game.state) {
            case GameState::MainMenu: menu_render();    break;
            case GameState::Playing:  playing_render(); break;
            default: break;
        }

        SDL_RenderPresent(game.renderer);
    }
}

void shutdown_game() {

    if (game.player.texture) {
        SDL_DestroyTexture(game.player.texture);
    }

    if (game.renderer) {
        SDL_DestroyRenderer(game.renderer);
    }

    if (game.window) {
        SDL_DestroyWindow(game.window);
    }

    SDL_Quit();
}