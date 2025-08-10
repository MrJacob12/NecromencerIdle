use crate::state::{GOLD, DAMAGE};

pub static mut UPGRADE_DAMAGE: u16 = 0;

#[no_mangle]
pub extern "C" fn upgrade_damage() {
    unsafe {
        let cost = calculate_damage_upgrade_cost(UPGRADE_DAMAGE);
        if GOLD >= cost && cost != 0 {
            GOLD -= cost;
            UPGRADE_DAMAGE += 1;
            DAMAGE += 5;
        }
    }
}

fn calculate_damage_upgrade_cost(upgrade: u16) -> u64 {
    if upgrade < 150 {
        100 + (upgrade as u64 * 125)
    } else {
        0
    }
}

#[no_mangle]
pub extern "C" fn get_upgrade_damage() -> u16 {
    unsafe {
        UPGRADE_DAMAGE
    }
}

#[no_mangle]
pub extern "C" fn get_upgrade_damage_cost() -> u64 {
    unsafe {
        calculate_damage_upgrade_cost(UPGRADE_DAMAGE)
    }
}