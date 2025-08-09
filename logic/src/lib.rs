mod state;
mod save;
mod mob_fight;

use state::{MOB_HP, MOB_MAX_HP, GOLD};
use save::{import_save, export_save, GameState};
use mob_fight::fighting;


static mut LAST_TICK: u64 = 0;

#[no_mangle]
pub extern "C" fn tick(current_time: u64) {
    unsafe {
        if current_time - LAST_TICK >= 1 {
            fighting();

            LAST_TICK = current_time;
        }
    }
}

#[no_mangle]
pub extern "C" fn get_gold() -> u64 {
    unsafe { GOLD }
}

#[no_mangle]
pub extern "C" fn get_mob_hp() -> u64 {
    unsafe { MOB_HP }
}

#[no_mangle]
pub extern "C" fn get_mob_max_hp() -> u64 {
    unsafe { MOB_MAX_HP }
}

#[no_mangle]
pub extern "C" fn get_mana() -> u64 {
    unsafe { MANA }
}

#[used]
#[no_mangle]
pub static _FORCE_LINK_IMPORT: extern "C" fn(*const GameState) = import_save;

#[used]
#[no_mangle]
pub static _FORCE_LINK_EXPORT: extern "C" fn(*mut GameState) = export_save;