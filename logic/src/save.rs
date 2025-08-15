use crate::state::*;
use crate::upgrades::{UPGRADE_DAMAGE, UPGRADE_MOB_LEVEL};

#[repr(C)]
pub struct GameState {
    pub gold: u64,
    pub mana: u64,
    pub damage: u64,

    pub mob_hp: u64,
    pub mob_max_hp: u64,
    pub mob_level: u64,
    pub mob_kill_count: u64,


    pub skeletons: u64,

    pub upgrade_damage: u16,
    pub upgrade_mob_level: u16,

    pub inventory: [u16; 10],
    pub inventory_amounts: [u64; 10],
}


#[no_mangle]
pub extern "C" fn import_save(state: *const GameState) {
    unsafe {
        if let Some(state) = state.as_ref() {
            GOLD = state.gold;
            MANA = state.mana;
            DAMAGE = if state.damage != 0 { state.damage } else { 10 };

            MOB_HP = if state.mob_hp != 0 { state.mob_hp } else { 100 };
            MOB_MAX_HP = if state.mob_max_hp != 0 { state.mob_max_hp } else { 100 };
            MOB_LEVEL = if state.mob_level != 0 { state.mob_level } else { 1 };
            MOB_KILL_COUNT = state.mob_kill_count;

            UPGRADE_DAMAGE = state.upgrade_damage;
            UPGRADE_MOB_LEVEL = state.upgrade_mob_level;

            SKELETONS = state.skeletons;

            if state.inventory.is_empty() || state.inventory_amounts.is_empty() {
                INVENTORY = [0; 10];
                INVENTORY_AMOUNTS = [0; 10];
            } else {
                for i in 0..10 {
                    INVENTORY[i] = state.inventory[i];
                    INVENTORY_AMOUNTS[i] = state.inventory_amounts[i];
                }
            }
        }
    }
}

#[no_mangle]
pub extern "C" fn export_save(state: *mut GameState) {
    unsafe {
        if let Some(state) = state.as_mut() {
            state.gold = GOLD;
            state.mana = MANA;
            state.damage = DAMAGE;

            state.mob_hp = MOB_HP;
            state.mob_max_hp = MOB_MAX_HP;
            state.mob_level = MOB_LEVEL;
            state.mob_kill_count = MOB_KILL_COUNT;

            state.skeletons = SKELETONS;
            state.upgrade_damage = UPGRADE_DAMAGE;
            state.upgrade_mob_level = UPGRADE_MOB_LEVEL;

            for i in 0..10 {
                state.inventory[i] = INVENTORY[i];
                state.inventory_amounts[i] = INVENTORY_AMOUNTS[i];
            }
        }
    }
}
