#include "ui.h"
#include "../logic.h"
#include "position.h"
#include <stdio.h>
#include <string.h>



void ui_render(SDL_Renderer* renderer, TTF_Font* font) {

    //* Gold
    draw_gold_coin(renderer);
    draw_gold(renderer, font, get_gold());

    //* Goblin Texture
    draw_mob(renderer);

    //* Mob HP
    draw_mob_hp(renderer, font);
}

void ui_cleanup() {
    
}
