#ifndef LOGIC_H
#define LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned long long get_gold();
unsigned long long get_mob_hp();
unsigned long long get_mob_max_hp();
unsigned long long get_mob_cooldown();


void tick(unsigned long long current_time);

#ifdef __cplusplus
}
#endif

#endif
