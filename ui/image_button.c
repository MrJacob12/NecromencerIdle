#include <math.h>
#include "image_button.h"
#include "texture.h"

ImageButton create_image_button(SDL_Renderer* renderer,
                                            const char* normal_path,
                                            const char* hover_path,
                                            UIPosition pos,
                                            ImageButtonCallback cb,
                                            void* userdata) {
    ImageButton btn;
    btn.position = pos;
    btn.normal_tex = NULL;
    btn.hover_tex = NULL;
    btn.hovered = 0;
    btn.on_click = cb;
    btn.userdata = userdata;
    btn.renderer = renderer;
    
    btn.current_scale = 1.0f;
    btn.target_scale = 1.0f;
    btn.scale_speed = 4.0f;
    btn.last_update_time = SDL_GetTicks();

    btn.normal_tex = load_texture(renderer, normal_path);
    
    if (hover_path) {
        btn.hover_tex = load_texture(renderer, hover_path);
    }

    return btn;
}

void update_image_button_animation(ImageButton* btn) {
    Uint64 current_time = SDL_GetTicks();
    float delta_time = (current_time - btn->last_update_time) / 1000.0f;
    btn->last_update_time = current_time;
    
    if (fabsf(btn->current_scale - btn->target_scale) > 0.01f) {
        float diff = btn->target_scale - btn->current_scale;
        btn->current_scale += diff * btn->scale_speed * delta_time;
    } else {
        btn->current_scale = btn->target_scale;
    }
}

void draw_image_button(SDL_Renderer* renderer, ImageButton* btn) {
    update_image_button_animation(btn);
    
    float x, y;
    get_ui_position(renderer, btn->position, &x, &y);
    
    float scaled_width = btn->position.width * btn->current_scale;
    float scaled_height = btn->position.height * btn->current_scale;
    
    float offset_x = (btn->position.width - scaled_width) * 0.5f;
    float offset_y = (btn->position.height - scaled_height) * 0.5f;
    
    SDL_FRect rect = { 
        x + offset_x, 
        y + offset_y, 
        scaled_width, 
        scaled_height 
    };
    
    SDL_Texture* tex = btn->hovered && btn->hover_tex ? btn->hover_tex : btn->normal_tex;
    if (tex) {
        SDL_RenderTexture(renderer, tex, NULL, &rect);
    }
}

void handle_image_button_event(ImageButton* btn, SDL_Event* e) {
    float x, y;
    get_ui_position(btn->renderer, btn->position, &x, &y);

    if (e->type == SDL_EVENT_MOUSE_MOTION) {
        float mx = e->motion.x;
        float my = e->motion.y;
        int was_hovered = btn->hovered;
        btn->hovered = (mx >= x && mx <= x + btn->position.width &&
                        my >= y && my <= y + btn->position.height);
        
        if (btn->hovered && !was_hovered) {
            btn->target_scale = 1.1f;
        } else if (!btn->hovered && was_hovered) {
            btn->target_scale = 1.0f;
        }
    }
    
    if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN && btn->hovered) {
        btn->target_scale = 0.95f;
        
        if (btn->on_click) {
            btn->on_click(btn->userdata);
        }

        SDL_Delay(50);
        btn->target_scale = btn->hovered ? 1.1f : 1.0f;
    }
}

void destroy_image_button(ImageButton* btn) {
    if (btn->normal_tex) SDL_DestroyTexture(btn->normal_tex);
    if (btn->hover_tex) SDL_DestroyTexture(btn->hover_tex);
}