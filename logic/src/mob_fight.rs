use crate::state::{GOLD, MOB_HP, MOB_MAX_HP, DAMAGE, MOB_KILL_COUNT, MOB_LEVEL};

static mut WAITING_FOR_NEXT_MOB: bool = false;
static mut NEXT_MOB_TIMER: u64 = 0;
static mut NEXT_MOB_COOLDOWN: u64 = 5;

pub fn fighting() {
    unsafe {
        if MOB_HP <= 0 && !WAITING_FOR_NEXT_MOB {
                WAITING_FOR_NEXT_MOB = true;
                GOLD += get_gold_per_kill(MOB_MAX_HP);

                MOB_KILL_COUNT += 1;
            }
            else {
                MOB_HP = MOB_HP.saturating_sub(DAMAGE);
            }
            
            if WAITING_FOR_NEXT_MOB {
                NEXT_MOB_TIMER += 1;
                if NEXT_MOB_TIMER >= NEXT_MOB_COOLDOWN {
                    MOB_HP = calculate_mob_hp();
                    MOB_MAX_HP = MOB_HP;

                    WAITING_FOR_NEXT_MOB = false;
                    NEXT_MOB_TIMER = 0;
                }
            }
    }
}

#[no_mangle]
pub extern "C" fn get_mob_cooldown() -> u64 {
    unsafe { NEXT_MOB_COOLDOWN - NEXT_MOB_TIMER }
}

#[no_mangle]
pub extern "C" fn get_mob_level() -> u64 {
    unsafe { MOB_LEVEL }
}

fn calculate_mob_hp() -> u64 {
    unsafe {
        100 + (MOB_LEVEL * 225)
    }
}

fn get_gold_per_kill(_mob_hp: u64) -> u64 {
    unsafe {
        let base_gold = 125 + (MOB_LEVEL * 5);
        base_gold + MOB_KILL_COUNT + (MOB_MAX_HP / 10)
    }
}

#[no_mangle]
pub extern "C" fn get_mob_kill_count() -> u64 {
    unsafe { MOB_KILL_COUNT }
}