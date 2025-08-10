#include "text.h"
#include "../utils/number_format.h"

void draw_gold(SDL_Renderer* renderer, TTF_Font* font, unsigned long long gold) {
    char gold_text[50];
    format_number(gold, gold_text, sizeof(gold_text));

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, gold_text, strlen(gold_text), white);
    if (!surface) {
        SDL_Log("Could not create surface: %s", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    float x, y;
    UIPosition pos = {
        .anchor = POS_TOP_LEFT,
        .offset_x = 50,
        .offset_y = 13,
        .width = (float)surface->w,
        .height = (float)surface->h
    };
    get_ui_position(renderer, pos, &x, &y);

    SDL_FRect dstrect = {x, y, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void draw_mana(SDL_Renderer* renderer, TTF_Font* font, unsigned long long mana) {
    char mana_text[50];
    format_number(mana, mana_text, sizeof(mana_text));

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, mana_text, strlen(mana_text), white);
    if (!surface) {
        SDL_Log("Could not create surface: %s", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    float x, y;
    UIPosition pos = {
        .anchor = POS_TOP_LEFT,
        .offset_x = 150,
        .offset_y = 13,
        .width = (float)surface->w,
        .height = (float)surface->h
    };
    get_ui_position(renderer, pos, &x, &y);
    
    SDL_FRect dstrect = {x, y, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void draw_mob_hp(SDL_Renderer* renderer, TTF_Font* font) {
    char mob_hp_text[50];

    if (get_mob_hp() <= 0) {
        sprintf(mob_hp_text, "Next mob in: %llus", get_mob_cooldown());
    } else {
        sprintf(mob_hp_text, "%llu/%llu", get_mob_hp(), get_mob_max_hp());
    }

    SDL_Color color = {239, 82, 87, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, mob_hp_text, 0, color);
    if (!surface) {
        SDL_Log("Could not create surface: %s", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    float box_width = 250.0f;
    float x, y;
    UIPosition pos = {
        .anchor = POS_CENTER,
        .offset_x = 0,
        .offset_y = 90,
        .width = box_width,
        .height = (float)surface->h
    };
    get_ui_position(renderer, pos, &x, &y);

    x += (box_width - surface->w) / 2.0f;

    SDL_FRect dstrect = {x, y, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(renderer, texture, NULL, &dstrect);


    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void draw_upgrade_damage(SDL_Renderer* renderer, TTF_Font* font) {
    char damage_text[50];
    char cost_text[50];

    format_number(get_upgrade_damage_cost(), cost_text, sizeof(cost_text));

    sprintf(damage_text, "Damage Upgrade: +5 Level: %hu Cost: %s", get_upgrade_damage(), cost_text);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, damage_text, 0, color);
    if (!surface) {
        SDL_Log("Could not create surface: %s", SDL_GetError());
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    float x, y;
    UIPosition pos = {
        .anchor = POS_TOP_LEFT,
        .offset_x = 50,
        .offset_y = 100,
        .width = (float)surface->w,
        .height = (float)surface->h
    };
    get_ui_position(renderer, pos, &x, &y);
    
    SDL_FRect dstrect = {x, y, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);

}

void draw_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, UIPosition pos, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, strlen(text), color);
    if (!surface) {
        SDL_Log("Could not create surface: %s", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    float x, y;
    get_ui_position(renderer, pos, &x, &y);

    SDL_FRect dstrect = {x, y, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}