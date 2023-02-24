include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

pub fn read(address: u32) -> u32 {
    unsafe { peek(address) }
}

pub fn write(address: u32, value: u32) {
    unsafe { poke(address, value) };
}
