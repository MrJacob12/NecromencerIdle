use crate::state::{GOLD};

#[repr(C)]
pub struct GameState {
    pub gold: u64,
}

#[no_mangle]
pub extern "C" fn import_save(state: *const GameState) {
    unsafe {
        if let Some(state) = state.as_ref() {
            GOLD = state.gold;
        }
    }
}

#[no_mangle]
pub extern "C" fn export_save(state: *mut GameState) {
    unsafe {
        if let Some(state) = state.as_mut() {
            state.gold = GOLD;
        }
    }
}
