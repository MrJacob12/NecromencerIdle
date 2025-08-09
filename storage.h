#ifndef STORAGE_H
#define STORAGE_H

typedef struct {
    unsigned long long gold;
    unsigned long long mana;
    unsigned long long damage;
    unsigned long long mob_hp;
    unsigned long long mob_max_hp;

    unsigned short inventory[12];
    unsigned long long inventory_amounts[12];
} GameState;

void save_game_state(GameState* state);
void load_game_state(GameState* state);

extern void import_save(const GameState* state);
extern void export_save(GameState* state);

#endif
