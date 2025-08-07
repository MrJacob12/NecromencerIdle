#ifndef UI_H
#define UI_H

#include <SDL3/SDL.h>
// Textrure loading, drawing and management
#include "texture.h"
// Text rendering and management
#include "text.h"

void ui_render(SDL_Renderer* renderer, TTF_Font* font);
void ui_cleanup();



#endif
