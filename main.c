#include <SDL3/SDL.h>
#include <SDL_ttf.h>

#include <time.h>
#include <stdio.h>

#include "logic.h"
#include "storage.h"


void draw_gold(SDL_Renderer* renderer, TTF_Font* font){
    char gold_Text[50];
    sprintf(gold_Text, "Gold: %llu", get_gold());

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, gold_Text, strlen(gold_Text), white);
    if (!surface) {
        SDL_Log("Could not create surface: %s", SDL_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FRect dstrect = {10, 10, surface->w, surface->h};
    SDL_RenderTexture(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init failed: %s\n", SDL_GetError());
        return 1;
    }

    if(TTF_Init() < 0) {
        printf("SDL_ttf Init failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Necromancer Idle", 800, 600, SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("Fredoka.ttf", 24);
    if (!font) {
        SDL_Log("Could not load font: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, "opengl");

    GameState state = {0};
    load_game_state(&state);
    import_save(&state);

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        time_t current_time = time(NULL);
        tick((unsigned long long)current_time);

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        draw_gold(renderer, font);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    export_save(&state);
    save_game_state(&state);

    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
