// Renderer.cpp

#include "Renderer.h"

#include <cmath>
#include <string>

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* relative_path) {

    const char* base = SDL_GetBasePath();
    std::string folder;

    if (base != nullptr)
        folder = base;
    else
        folder = "";

    std::string path = folder + "../../" + relative_path;

    SDL_Surface* surface = SDL_LoadPNG(path.c_str());
    if (!surface) {
        SDL_Log("Failed to load %s: %s", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("Failed to create texture from %s: %s", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    return texture;
}

void draw_character(
    SDL_Renderer* renderer,
    const Character& character,
    const Camera& camera
) {

    if (!character.texture) return;

    SDL_FRect src = {
        character.sprite_column * (float)SPRITE_FRAME_SIZE,
        character.sprite_row * (float)SPRITE_FRAME_SIZE,
        SPRITE_FRAME_SIZE,
        SPRITE_FRAME_SIZE
    };

    float screen_x = (character.x + character.offset_x - camera.x) * camera.zoom;
    float screen_y = (character.y + character.offset_y - camera.y) * camera.zoom;

    float draw_size = TILE_SIZE * camera.zoom;

    SDL_FRect dst = {
        screen_x,
        screen_y,
        draw_size,
        draw_size
    };

    SDL_RenderTexture(renderer, character.texture, &src, &dst);
}

void draw_grid(SDL_Renderer* renderer, const Camera& camera) {

    SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);

    for (int i = 0; i <= 10; i++) {
        float p = i * TILE_SIZE;

        // vertical line
        SDL_RenderLine(renderer,
            (p - camera.x) * camera.zoom, (0 - camera.y) * camera.zoom,
            (p - camera.x) * camera.zoom, (10 * TILE_SIZE - camera.y) * camera.zoom);

        // horizontal line
        SDL_RenderLine(renderer,
            (0 - camera.x) * camera.zoom, (p - camera.y) * camera.zoom,
            (10 * TILE_SIZE - camera.x) * camera.zoom, (p - camera.y) * camera.zoom);
    }
}

void draw_filled_oval(
    SDL_Renderer* renderer,
    int center_x,
    int center_y,
    int radius_x,
    int radius_y
) {

    for (int dy = -radius_y; dy <= radius_y; dy++) {
        float t = (float)dy / radius_y;
        float dx = radius_x * std::sqrt(1.0f - t * t);

        SDL_RenderLine(
            renderer,
            center_x - dx, center_y + dy,
            center_x + dx, center_y + dy
        );
    }
}