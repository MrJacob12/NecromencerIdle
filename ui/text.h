#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <SDL_ttf.h>

#include "position.h"
#include "../logic.h"

void draw_gold(SDL_Renderer* renderer, TTF_Font* font, unsigned long long gold);
void draw_mob_hp(SDL_Renderer* renderer, TTF_Font* font);
void draw_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, UIPosition pos, SDL_Color color);

#endif
