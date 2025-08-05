static mut LAST_TICK: u64 = 0;
static mut GOLD: u64 = 0;

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
