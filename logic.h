#ifndef LOGIC_H
#define LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned long long get_gold();
unsigned long long get_mob_hp();
unsigned long long get_mob_max_hp();
unsigned long long get_mob_cooldown();
unsigned long long get_mana();
unsigned long long get_damage();
unsigned long long get_upgrade_damage_cost();
unsigned short get_upgrade_damage();


void tick(unsigned long long current_time);
void upgrade_damage();

#ifdef __cplusplus
}
#endif

#endif
