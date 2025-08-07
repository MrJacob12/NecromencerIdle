#include "texture.h"

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Failed to load image %s: %s", path, SDL_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("Failed to create texture from %s: %s", path, SDL_GetError());
        return NULL;
    }

    SDL_SetTextureScaleMode(texture, 0);
    return texture;
}

void draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, float x, float y, float w, float h) {
    if (!texture) return;
    SDL_FRect dst = {x, y, w, h};
    SDL_RenderTexture(renderer, texture, NULL, &dst);
}
