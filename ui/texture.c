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

void draw_gold_icon(SDL_Renderer* renderer) {
    static SDL_Texture* gold_icon = NULL;
    if (!gold_icon) {
        gold_icon = load_texture(renderer, "assets/gold_icon.png");
    }
    float x, y;
    UIPosition pos = {
        .anchor = POS_TOP_LEFT,
        .offset_x = 10,
        .offset_y = 12,
        .width = 32,
        .height = 32
    };
    get_ui_position(renderer, pos, &x, &y);
    draw_texture(renderer, gold_icon, x, y, 32, 32);
}

void draw_mob(SDL_Renderer* renderer) {
     static SDL_Texture* goblin = NULL;
    if (!goblin) {
        goblin = load_texture(renderer, "assets/goblin.png");
    }

    float x, y;
    UIPosition pos = {
        .anchor = POS_CENTER,
        .offset_x = 0,
        .offset_y = 10,
        .width = 128,
        .height = 128
    };
    get_ui_position(renderer, pos, &x, &y);
    if(get_mob_hp() > 0) {
        draw_texture(renderer, goblin, x, y, 128, 128);
    }
}

void draw_mana_icon(SDL_Renderer* renderer) {
    static SDL_Texture* mana_icon = NULL;
    if (!mana_icon) {
        mana_icon = load_texture(renderer, "assets/mana_icon.png");
    }
    
    float x, y;
    UIPosition pos = {
        .anchor = POS_TOP_LEFT,
        .offset_x = 130,
        .offset_y = 12,
        .width = 32,
        .height = 32
    };
    get_ui_position(renderer, pos, &x, &y);
    draw_texture(renderer, mana_icon, x, y, 32, 32);
}
