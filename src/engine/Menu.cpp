

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

    for (int i = 0; i < MENU_COUNT; i++) {
        if ( i == game.menu.selected ) {
            SDL_SetRenderDrawColor(game.renderer, 255, 220, 0, 255);
        }
        else
            SDL_SetRenderDrawColor(game.renderer, 200, 200, 200, 255);

        SDL_RenderDebugText(game.renderer, game.screen_width/2, game.screen_height/2 + i * 20.0f, MENU_ITEMS[i]);
    }
}