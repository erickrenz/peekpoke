//! # peekpoke
//!
//! `peekpoke` is a lightweight Rust library for accessing physical
//! memory addresses using /dev/mem in Linux systems.

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));


/// Reads from the physical memory address given.
///
/// # Example
///
/// ```
/// let address: u32 = 0x4000_0000;
///
/// let value: u32 = peekpoke::read(address);
///
/// println!("{:#010X}", value); // 0x0000_0000 
/// ```
///
/// # Return type
///
/// The C return type of this function is `::std::os::raw::c_uint`.
/// The Rust equivalent return type is `u32`.
///
/// This function will always return a `u32` (equivalent to one 8-digit 
/// hexadecimal number) unless a panic has occurred.
///
/// # Panics
///
/// Within this function, there are only two possible causes for a panic
///
/// 1. **Unable to open `/dev/mem`.** This can be caused by not using a
/// Linux operating systems, or by not having the proper permissions to
/// interact with this file.
/// 2. **Address is not valid.** This can be caused by trying to access
/// an address that is not mapped to any physical hardware.
///
/// # Safety
///
/// The read function is a wrapper for the unsafe function "peek".
/// The `peek` function was initially written in C. It is wrapped 
/// in an unsafe block since it directly interacts with the physical
/// memory in your system.
pub fn read(address: u32) -> u32 {
    unsafe { peek(address) }
}

/// Writes the value given to the physical memory address.
///
/// # Example
///
/// ```
/// let address: u32 = 0x4000_0000;
/// let value: u32 = 0xDEAD_BEEF;
///
/// peekpoke::write(address, value);
///
/// let result: u32 = peekpoke::read(address);
/// println!("{:#010X}", result); // 0xDEAD_BEEF 
/// ```
///
/// # Return type
///
/// This function will always return void. If a panic has occurred within
/// this function, then the rest of your script will not complete.
///
/// # Panics
///
/// Within this function, there are only two possible causes for a panic
///
/// 1. **Unable to open `/dev/mem`.** This can be caused by not using a
/// Linux operating systems, or by not having the proper permissions to
/// interact with this file.
/// 2. **Address is not valid.** This can be caused by trying to access
/// an address that is not mapped to any physical hardware.
///
/// # Safety
///
/// The read function is a wrapper for the unsafe function "peek".
/// The `peek` function was initially written in C. It is wrapped 
/// in an unsafe block since it directly interacts with the physical
/// memory in your system.
pub fn write(address: u32, value: u32) {
    unsafe { poke(address, value) };
}
