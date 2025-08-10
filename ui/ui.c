#include "ui.h"
#include "../logic.h"
#include "position.h"
#include "button.h"
#include "scene.h"
#include <stdio.h>
#include <string.h>

static Button upgrades_btn;
static Button upgrades_close_btn;
static Button buy_damage_upgrade_bnt;

static int ui_initialized = 0;

void open_upgrades(void* userdata) {
    current_scene = SCENE_UPGRADES;
}

void close_upgrades(void* userdata) {
    current_scene = SCENE_GAME;
}

void buy_damage_upgrade_callback(void* userdata) {
    upgrade_damage();
}

void ui_init(TTF_Font* font) {
    upgrades_btn = create_button(
        650, 20, 120, 40,
        "Upgrade",
        font,
        (SDL_Color){60,60,200,255},
        (SDL_Color){100,100,250,255},
        (SDL_Color){255,255,255,255},
        open_upgrades, NULL
    );

    upgrades_close_btn = create_button(
        650, 20, 120, 40,
        "Close",
        font,
        (SDL_Color){200,60,60,255},
        (SDL_Color){250,100,100,255},
        (SDL_Color){255,255,255,255},
        close_upgrades, NULL
    );

    buy_damage_upgrade_bnt = create_button(
        50, 150, 200, 40,
        "Buy",
        font,
        (SDL_Color){60,200,60,255},
        (SDL_Color){100,250,100,255},
        (SDL_Color){255,255,255,255},
        buy_damage_upgrade_callback, NULL
    );


    ui_initialized = 1;
}

void ui_render(SDL_Renderer* renderer, TTF_Font* font) {
    if (!ui_initialized) ui_init(font);

    if (current_scene == SCENE_GAME) {
        draw_gold_coin(renderer);
        draw_gold(renderer, font, get_gold());

        draw_mana(renderer, font, get_mana());

        draw_mob(renderer);
        draw_mob_hp(renderer, font);

        draw_button(renderer, &upgrades_btn);
    }
    else if (current_scene == SCENE_UPGRADES) {
        draw_gold_coin(renderer);
        draw_gold(renderer, font, get_gold());

        // Upgrades 
        draw_upgrade_damage(renderer, font);
        if (get_upgrade_damage_cost() >= get_gold()) {
            buy_damage_upgrade_bnt.bg_color = (SDL_Color){200,60,60,255}; 
            buy_damage_upgrade_bnt.hover_color = (SDL_Color){250,100,100,255};
            strncpy(buy_damage_upgrade_bnt.label, "Not enough gold", sizeof(buy_damage_upgrade_bnt.label)-1);
        }
        else if (get_upgrade_damage_cost() == 0) {
            strncpy(buy_damage_upgrade_bnt.label, "Maxed", sizeof(buy_damage_upgrade_bnt.label)-1);
        }
        else {
            buy_damage_upgrade_bnt.bg_color = (SDL_Color){60,200,60,255};
            buy_damage_upgrade_bnt.hover_color = (SDL_Color){100,250,100,255};
            snprintf(buy_damage_upgrade_bnt.label, sizeof(buy_damage_upgrade_bnt.label), "Buy");
        }
        draw_button(renderer, &buy_damage_upgrade_bnt);

        draw_button(renderer, &upgrades_close_btn);
    }
}

void ui_handle_event(SDL_Event* e) {
    if (current_scene == SCENE_GAME) {
        handle_button_event(&upgrades_btn, e);
    }
    else if (current_scene == SCENE_UPGRADES) {
        handle_button_event(&upgrades_close_btn, e);
        handle_button_event(&buy_damage_upgrade_bnt, e);
    }
}

void ui_cleanup() {
    ui_initialized = 0;
}
