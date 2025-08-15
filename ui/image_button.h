#ifndef IMAGE_BUTTON_H
#define IMAGE_BUTTON_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "position.h"

typedef void (*ImageButtonCallback)(void* userdata);

typedef struct {
    UIPosition position;
    SDL_Texture* normal_tex;
    SDL_Texture* hover_tex;
    int hovered;
    ImageButtonCallback on_click;
    void* userdata;
    SDL_Renderer* renderer;

    float current_scale;
    float target_scale;
    float scale_speed;
    Uint64 last_update_time;
} ImageButton;

ImageButton create_image_button(SDL_Renderer* renderer,
                                const char* normal_path,
                                const char* hover_path,
                                UIPosition pos,
                                ImageButtonCallback cb,
                                void* userdata);

void draw_image_button(SDL_Renderer* renderer, ImageButton* btn);
void handle_image_button_event(ImageButton* btn, SDL_Event* e);
void destroy_image_button(ImageButton* btn);

#endif
