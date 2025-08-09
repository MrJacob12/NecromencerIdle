use crate::state::{GOLD, DAMAGE, MOB_HP, MOB_MAX_HP};

#[repr(C)]
pub struct GameState {
    pub gold: u64,
    pub mana: u64,
    pub damage: u64,
    pub mob_hp: u64,
    pub mob_max_hp: u64,
}

#[repr(C)]
pub struct Inventory {
    pub items: [u16; 12],
    pub amounts: [u64; 12],
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

            if state.inventory.is_empty() || state.inventory_amounts.is_empty() {
                INVENTORY = [0; 10];
                INVENTORY_AMOUNTS = [0; 10];
            } else {
                for i in 0..12 {
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

            for i in 0..12 {
                state.inventory[i] = INVENTORY[i];
                state.inventory_amounts[i] = INVENTORY_AMOUNTS[i];
            }
        }
    }
}
