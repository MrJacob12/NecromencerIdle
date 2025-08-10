
#include <stdio.h>
#include <time.h>

#include "storage.h"
#include "logic.h"
#include "ui/ui.h"

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

    TTF_Font* font_medium = TTF_OpenFont("Ubuntu-Regular.ttf", 24);


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
            ui_handle_event(&event);
        }

        time_t current_time = time(NULL);
        tick((unsigned long long)current_time);

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        ui_render(renderer, font_medium);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    export_save(&state);
    save_game_state(&state);

    ui_cleanup();

    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font_medium);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
