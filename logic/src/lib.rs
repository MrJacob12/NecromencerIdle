mod state;
mod save;

use state::GOLD;
use save::{import_save, export_save, GameState};

static mut LAST_TICK: u64 = 0;

#[no_mangle]
pub extern "C" fn tick(current_time: u64) {
    unsafe {
        if current_time - LAST_TICK >= 5 {
            GOLD += 1;
            LAST_TICK = current_time;
        }
    }
}

#[no_mangle]
pub extern "C" fn get_gold() -> u64 {
    unsafe { GOLD }
}

#[used]
#[no_mangle]
pub static _FORCE_LINK_IMPORT: extern "C" fn(*const GameState) = import_save;

#[used]
#[no_mangle]
pub static _FORCE_LINK_EXPORT: extern "C" fn(*mut GameState) = export_save;