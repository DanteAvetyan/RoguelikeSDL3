

#include "Game.h"
#include "Menu.h"
static const char* MENU_ITEMS[] = {"Start", "Quit"};
static const int MENU_COUNT = 2;

void menu_input(const SDL_Event& event) {
    if (event.type != SDL_EVENT_KEY_DOWN) return;

    switch (event.key.key) {
        case SDLK_W:
        case SDLK_UP:
            game.menu.selected = (game.menu.selected - 1 + MENU_COUNT) % MENU_COUNT; break;
        case SDLK_S:
        case SDLK_DOWN:
            game.menu.selected = (game.menu.selected + 1) % MENU_COUNT; break;
        case SDLK_RETURN:
            if (game.menu.selected == 0) game.state = GameState::Playing;
            if (game.menu.selected == 1) game.state = GameState::Quit;
            break;
        case SDLK_M:
            game.state = GameState::MainMenu;
    }
}

void menu_render() {

    if (!game.font) return;

    for (int i = 0; i < MENU_COUNT; i++) {
        SDL_Color color;
        if ( i == game.menu.selected ) {
            color = {255, 220, 0, 255};
        }
        else
            color = {200, 200, 200, 255};

        SDL_Surface* surface = TTF_RenderText_Solid(game.font, MENU_ITEMS[i], 0, color);
        if (!surface) continue;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(game.renderer, surface);
        if (!texture) continue;

        float w,h;
        SDL_GetTextureSize(texture, &w, &h);

        SDL_FRect dst = {
            (float)game.screen_width/2,
            (float)game.screen_height/2.0f + i * 50.0f,
            w,
            h
        };

        SDL_RenderTexture(game.renderer, texture, nullptr, &dst);
        SDL_DestroyTexture(texture);

    }
}