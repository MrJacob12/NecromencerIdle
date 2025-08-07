use crate::state::{GOLD, DAMAGE, MOB_HP, MOB_MAX_HP};

#[repr(C)]
pub struct GameState {
    pub gold: u64,
    pub damage: u64,
    pub mob_hp: u64,
    pub mob_max_hp: u64,
}

#[no_mangle]
pub extern "C" fn import_save(state: *const GameState) {
    unsafe {
        if let Some(state) = state.as_ref() {
            GOLD = state.gold;
            DAMAGE = if state.damage != 0 { state.damage } else { 10 };
            MOB_HP = if state.mob_hp != 0 { state.mob_hp } else { 100 };
            MOB_MAX_HP = if state.mob_max_hp != 0 { state.mob_max_hp } else { 100 };
        }
    }
}

#[no_mangle]
pub extern "C" fn export_save(state: *mut GameState) {
    unsafe {
        if let Some(state) = state.as_mut() {
            state.gold = GOLD;
            state.damage = DAMAGE;
            state.mob_hp = MOB_HP;
            state.mob_max_hp = MOB_MAX_HP;
        }
    }
}
