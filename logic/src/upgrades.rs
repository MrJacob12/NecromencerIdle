use crate::state::{GOLD, DAMAGE, MOB_LEVEL};

pub static mut UPGRADE_DAMAGE: u16 = 0;
static mut UPGRADE_DAMAGE_MAX_LEVEL: u16 = 150;

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
    unsafe {
        if upgrade < UPGRADE_DAMAGE_MAX_LEVEL {
            100 + (upgrade as u64 * 125)
        } else {
            0
        }
    }
}

#[no_mangle]
pub extern "C" fn get_upgrade_damage_level()-> u16 {
    unsafe {
        UPGRADE_DAMAGE
    }
}

#[no_mangle]
pub extern "C" fn get_upgrade_damage_max_level() -> u16 {
    unsafe {
        UPGRADE_DAMAGE_MAX_LEVEL
    }
}

#[no_mangle]
pub extern "C" fn get_upgrade_damage_cost() -> u64 {
    unsafe {
        calculate_damage_upgrade_cost(UPGRADE_DAMAGE)
    }
}

pub static mut UPGRADE_MOB_LEVEL: u16 = 0;
static mut UPGRADE_MOB_MAX_LEVEL: u16 = 15;

#[no_mangle]
pub extern "C" fn upgrade_mob_level() {
    unsafe {
        let cost = calculate_mob_upgrade_cost(UPGRADE_MOB_LEVEL);
        if GOLD >= cost && cost != 0 {
            GOLD -= cost;
            UPGRADE_MOB_LEVEL += 1;
            MOB_LEVEL += 1;
        }
    }
}

fn calculate_mob_upgrade_cost(upgrade: u16) -> u64 {
    unsafe {
        if upgrade < UPGRADE_MOB_MAX_LEVEL {
            500 + (upgrade as u64 * 250)
        } else {
            0
        }
    }
}

#[no_mangle]
pub extern "C" fn get_upgrade_mob_level_level() -> u16 {
    unsafe {
        UPGRADE_MOB_LEVEL
    }
}
#[no_mangle]
pub extern "C" fn get_upgrade_mob_level_max_level() -> u16 {
    unsafe {
        UPGRADE_MOB_MAX_LEVEL
    }
}

#[no_mangle]
pub extern "C" fn get_upgrade_mob_level_cost() -> u64 {
    unsafe {
        calculate_mob_upgrade_cost(UPGRADE_MOB_LEVEL)
    }
}
