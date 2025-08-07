#include "text.h"


void draw_gold(SDL_Renderer* renderer, TTF_Font* font, unsigned long long gold) {
    char gold_text[50];
    sprintf(gold_text, "Gold: %llu", gold);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, gold_text, strlen(gold_text), white);
    if (!surface) {
        SDL_Log("Could not create surface: %s", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    float x, y;
    UIPosition pos = {
        .anchor = POS_TOP_LEFT,
        .offset_x = 10,
        .offset_y = 10,
        .width = (float)surface->w,
        .height = (float)surface->h
    };
    get_ui_position(renderer, pos, &x, &y);

    SDL_FRect dstrect = {x, y, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}
