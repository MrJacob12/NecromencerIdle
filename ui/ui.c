#include "ui.h"
#include "../logic.h"
#include "position.h"
#include "button.h"
#include "image_button.h"
#include "scene.h"
#include <stdio.h>
#include <string.h>

static ImageButton upgrades_btn;
static ImageButton upgrades_close_btn;
static Button buy_damage_upgrade_bnt;
static Button buy_mob_level_upgrade_bnt;

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

void buy_mob_level_upgrade_callback(void* userdata) {
    upgrade_mob_level();
}

void ui_init(TTF_Font* font, SDL_Renderer* renderer) {
    upgrades_btn = create_image_button(
       renderer,
        "assets/upgrades_button_normal.png",
        "assets/upgrades_button_normal.png",
        (UIPosition){
            .anchor = POS_TOP_RIGHT,
            .offset_x = -5,
            .offset_y = 10,
            .width = 64,
            .height = 64
        },
        open_upgrades, NULL
    );

    upgrades_close_btn = create_image_button(
        renderer,
        "assets/close_button_normal.png",
        "assets/close_button_normal.png",
        (UIPosition){
            .anchor = POS_TOP_RIGHT,
            .offset_x = -5,
            .offset_y = 10,
            .width = 64,
            .height = 64
        },
        close_upgrades, NULL
    );

    buy_damage_upgrade_bnt = create_button(
        240, 145, 200, 40,
        "Buy",
        font,
        (SDL_Color){60,200,60,255},
        (SDL_Color){100,250,100,255},
        (SDL_Color){255,255,255,255},
        buy_damage_upgrade_callback, NULL
    );

    buy_mob_level_upgrade_bnt = create_button(
        240, 250, 200, 40,
        "Buy",
        font,
        (SDL_Color){60,200,60,255},
        (SDL_Color){100,250,100,255},
        (SDL_Color){255,255,255,255},
        buy_mob_level_upgrade_callback, NULL
    );

    ui_initialized = 1;
}

void ui_render(SDL_Renderer* renderer, TTF_Font* font) {
    if (!ui_initialized) ui_init(font, renderer);

    if (current_scene == SCENE_GAME) {
        draw_gold(renderer, font, get_gold());
        draw_gold_icon(renderer, (UIPosition){
            .anchor = POS_TOP_LEFT,
            .offset_x = 10,
            .offset_y = 12,
            .width = 32,
            .height = 32
        });

        draw_mana(renderer, font, get_mana());
        draw_mana_icon(renderer);

        draw_mob_kill_icon(renderer);
        draw_mob_kill_count(renderer, font, get_mob_kill_count());

        draw_mob(renderer);
        draw_mob_hp(renderer, font);
        draw_mob_level(renderer, font);

        draw_image_button(renderer, &upgrades_btn);
    }
    else if (current_scene == SCENE_UPGRADES) {
        draw_gold(renderer, font, get_gold());
        draw_gold_icon(renderer, (UIPosition){
            .anchor = POS_TOP_LEFT,
            .offset_x = 10,
            .offset_y = 12,
            .width = 32,
            .height = 32
        });

        //! Upgrades 
        //* Damage Upgrade
        draw_upgrade_damage_level(renderer, font);
        draw_gold_icon(renderer, (UIPosition){
            .anchor = POS_TOP_LEFT,
            .offset_x = 50,
            .offset_y = 148,
            .width = 32,
            .height = 32
        });
        draw_upgrade_damage_cost(renderer, font);
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

        //* Mob Level Upgrade
        draw_upgrade_mob_level_level(renderer, font);
        draw_gold_icon(renderer, (UIPosition){
            .anchor = POS_TOP_LEFT,
            .offset_x = 50,
            .offset_y = 248,
            .width = 32,
            .height = 32
        });
        draw_upgrade_mob_level_cost(renderer, font);
        if (get_upgrade_mob_level_cost() >= get_gold()) {
            buy_mob_level_upgrade_bnt.bg_color = (SDL_Color){200,60,60,255}; 
            buy_mob_level_upgrade_bnt.hover_color = (SDL_Color){250,100,100,255};
            strncpy(buy_mob_level_upgrade_bnt.label, "Not enough gold", sizeof(buy_mob_level_upgrade_bnt.label)-1);
        }
        else if (get_upgrade_mob_level_cost() == 0) {
            strncpy(buy_mob_level_upgrade_bnt.label, "Maxed", sizeof(buy_mob_level_upgrade_bnt.label)-1);
        }
        else {
            buy_mob_level_upgrade_bnt.bg_color = (SDL_Color){60,200,60,255};
            buy_mob_level_upgrade_bnt.hover_color = (SDL_Color){100,250,100,255};
            snprintf(buy_mob_level_upgrade_bnt.label, sizeof(buy_mob_level_upgrade_bnt.label), "Buy");
        }
        draw_button(renderer, &buy_mob_level_upgrade_bnt);
        
        //* Close button
        draw_image_button(renderer, &upgrades_close_btn);
    }
}

void ui_handle_event(SDL_Event* e) {
    if (current_scene == SCENE_GAME) {
        handle_image_button_event(&upgrades_btn, e);
    }
    else if (current_scene == SCENE_UPGRADES) {
        handle_image_button_event(&upgrades_close_btn, e);
        handle_button_event(&buy_damage_upgrade_bnt, e);
        handle_button_event(&buy_mob_level_upgrade_bnt, e);
    }
}

void ui_cleanup() {
    ui_initialized = 0;
}
