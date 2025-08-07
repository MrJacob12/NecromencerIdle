#include "ui.h"
#include "../logic.h"
#include "position.h"
#include <stdio.h>
#include <string.h>



void ui_render(SDL_Renderer* renderer, TTF_Font* font) {
    draw_gold(renderer, font, get_gold());

    //* Goblin Texture
    static SDL_Texture* goblin = NULL;
    if (!goblin) {
        goblin = load_texture(renderer, "assets/goblin.png");
    }

    float x, y;
    UIPosition pos = {
        .anchor = POS_CENTER,
        .offset_x = 10,
        .offset_y = 10,
        .width = 128,
        .height = 128
    };
    get_ui_position(renderer, pos, &x, &y);

    draw_texture(renderer, goblin, x, y, 128, 128);
}

void ui_cleanup() {
    
}
