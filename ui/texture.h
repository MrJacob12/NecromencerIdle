#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_image.h>

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* path);
void draw_texture(SDL_Renderer* renderer, SDL_Texture* texture, float x, float y, float w, float h);

#endif