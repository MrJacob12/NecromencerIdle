#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>

#ifdef __APPLE__
    #include <SDL3_ttf/SDL_ttf.h>
#else
    #include <SDL_ttf.h>
#endif

#include "position.h"
#include "../logic.h"

void draw_gold(SDL_Renderer* renderer, TTF_Font* font, unsigned long long gold);
void draw_mana(SDL_Renderer* renderer, TTF_Font* font, unsigned long long mana);

void draw_mob_hp(SDL_Renderer* renderer, TTF_Font* font);
void draw_mob_level(SDL_Renderer* renderer, TTF_Font* font);

void draw_mob_kill_count(SDL_Renderer* renderer, TTF_Font* font, unsigned long long mob_kill_count);

void draw_upgrade_damage_level(SDL_Renderer* renderer, TTF_Font* font);
void draw_upgrade_damage_cost(SDL_Renderer* renderer, TTF_Font* font);

void draw_upgrade_mob_level_level(SDL_Renderer* renderer, TTF_Font* font);
void draw_upgrade_mob_level_cost(SDL_Renderer* renderer, TTF_Font* font);


void draw_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, UIPosition pos, SDL_Color color);

#endif
