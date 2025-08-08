#ifndef POSITION_H
#define POSITION_H

#include <SDL3/SDL.h>

typedef enum {
    POS_TOP_LEFT,
    POS_TOP_RIGHT,
    POS_BOTTOM_LEFT,
    POS_BOTTOM_RIGHT,
    POS_CENTER,
} UIPositionAnchor;

typedef struct {
    UIPositionAnchor anchor;
    float offset_x;
    float offset_y;
    float width;
    float height;
} UIPosition;

void get_ui_position(SDL_Renderer* renderer, UIPosition pos, float* out_x, float* out_y);

#endif