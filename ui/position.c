#include "position.h"

void get_ui_position(SDL_Renderer* renderer, UIPosition pos, float* out_x, float* out_y) {
    int w, h;
    SDL_GetCurrentRenderOutputSize(renderer, &w, &h);

    switch (pos.anchor) {
        case POS_TOP_LEFT:
            *out_x = pos.offset_x;
            *out_y = pos.offset_y;
            break;
        case POS_TOP_RIGHT:
            *out_x = w - pos.offset_x - pos.width;
            *out_y = pos.offset_y;
            break;
        case POS_BOTTOM_LEFT:
            *out_x = pos.offset_x;
            *out_y = h - pos.offset_y - pos.height;
            break;
        case POS_BOTTOM_RIGHT:
            *out_x = w - pos.offset_x - pos.width;
            *out_y = h - pos.offset_y - pos.height;
            break;
        case POS_CENTER:
            *out_x = (w - pos.width) / 2 + pos.offset_x;
            *out_y = (h - pos.height) / 2 + pos.offset_y;
            break;
    }
}
