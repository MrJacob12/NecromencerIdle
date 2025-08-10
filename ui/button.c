#include "button.h"
#include <string.h>

Button create_button(float x, float y, float w, float h,
                     const char* text, TTF_Font* font,
                     SDL_Color bg_color, SDL_Color hover_color,
                     SDL_Color text_color, ButtonCallback cb, void* userdata) {
    Button btn;
    btn.rect = (SDL_FRect){x, y, w, h};
    btn.bg_color = bg_color;
    btn.hover_color = hover_color;
    btn.text_color = text_color;
    btn.font = font;
    btn.hovered = 0;
    btn.on_click = cb;
    btn.userdata = userdata;
    strncpy(btn.label, text, sizeof(btn.label)-1);
    btn.label[sizeof(btn.label)-1] = '\0';
    return btn;
}

void draw_button(SDL_Renderer* renderer, Button* btn) {
    if (btn->hovered) {
        SDL_SetRenderDrawColor(renderer, btn->hover_color.r, btn->hover_color.g, btn->hover_color.b, btn->hover_color.a);
    } else {
        SDL_SetRenderDrawColor(renderer, btn->bg_color.r, btn->bg_color.g, btn->bg_color.b, btn->bg_color.a);
    }
    SDL_RenderFillRect(renderer, &btn->rect);

    SDL_Surface* surface = TTF_RenderText_Blended(btn->font, btn->label, 0, btn->text_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FRect text_rect = {
        btn->rect.x + (btn->rect.w - surface->w) / 2.0f,
        btn->rect.y + (btn->rect.h - surface->h) / 2.0f,
        (float)surface->w, (float)surface->h
    };
    SDL_RenderTexture(renderer, texture, NULL, &text_rect);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void handle_button_event(Button* btn, SDL_Event* e) {
    if (e->type == SDL_EVENT_MOUSE_MOTION) {
        float mx = e->motion.x;
        float my = e->motion.y;
        btn->hovered = (mx >= btn->rect.x && mx <= btn->rect.x + btn->rect.w &&
                        my >= btn->rect.y && my <= btn->rect.y + btn->rect.h);
    }
    if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN && btn->hovered) {
        if (btn->on_click) {
            btn->on_click(btn->userdata);
        }
    }
}
