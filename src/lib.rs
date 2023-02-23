#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

pub fn read(address: u32) -> u32 {
    unsafe { peek(address) }
}

pub fn write(address: u32, value: u32) -> i32 {
    unsafe { poke(address, value) }
}
