#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef __APPLE__
    #include <SDL3_image/SDL_image.h>
#else
    #include <SDL_image.h>
#endif



#include "../logic.h"
#include "position.h"

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* path);
void draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, float x, float y, float w, float h);

void draw_gold_coin(SDL_Renderer* renderer);
void draw_mob(SDL_Renderer* renderer);

#endif