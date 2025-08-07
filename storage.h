#ifndef STORAGE_H
#define STORAGE_H

typedef struct {
    unsigned long long gold;
} GameState;

void save_game_state(GameState* state);
void load_game_state(GameState* state);

extern void import_save(const GameState* state);
extern void export_save(GameState* state);

#endif
