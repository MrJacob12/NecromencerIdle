#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>

#ifdef __APPLE__
    #include <SDL3_ttf/SDL_ttf.h>
#else
    #include <SDL_ttf.h>
#endif

typedef void (*ButtonCallback)(void* userdata);

typedef struct {
    SDL_FRect rect;
    SDL_Color bg_color;
    SDL_Color hover_color;
    SDL_Color text_color;
    char label[64];
    TTF_Font* font;
    int hovered;
    ButtonCallback on_click;
    void* userdata;
} Button;

Button create_button(float x, float y, float w, float h,
                     const char* text, TTF_Font* font,
                     SDL_Color bg_color, SDL_Color hover_color,
                     SDL_Color text_color, ButtonCallback cb, void* userdata);

void draw_button(SDL_Renderer* renderer, Button* btn);
void handle_button_event(Button* btn, SDL_Event* e);

#endif
