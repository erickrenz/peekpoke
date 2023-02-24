# peekpoke

[![Latest Version]][crates.io] [![Documentation]][docs.rs] ![Downloads] ![License]

A lightweight Rust library used for reading and writing from physical memory using `/dev/mem`. 

In Linux, `/dev/mem` is a character device file containing access to the physical memory in a system. This file can be used to read and write to physical addresses on the bare metal (or virtualized) hardware.

Read the [kernel manual](https://man7.org/linux/man-pages/man4/mem.4.html) for more information.

## Requirements

- Linux (WSL, Debian, Fedora, Arch)
- Sudo permissions


## Usage

Add this to your `Cargo.toml`:

```toml
[dependencies]
peekpoke = "0.1.0"
```

## Example

```rust
// Write to address: 0x40000000 
//   ... with value: 0xFFFFFFFF
peekpoke::write(0x4000_0000, 0xFFFF_FFFF);

// Read from address: 0x40000000
let value: u32 = peekpoke::read(0x4000_0000);
println!("{:#010X}", value); // 0xFFFFFFFF
```

## Troubleshooting

### Access denied to /dev/mem

1. Configure your kernel with `CONFIG_STRICT_DEVMEM=n` (RECCOMENDED). The default kernel configuration denies access to RAM using `/dev/mem` (default: `CONFIG_STRICT_DEVMEM=y`) for non root users. 
1. Run as root user.

### Address invalid

The default behavior for `/dev/mem` is to return errors if the address you enter is invalid. Refer to your hardware's manual for further troubleshooting steps.

## Cross Compiling

For embedded systems development, it may be useful to cross compile your app to run on a different architecture. For more information on this process, check out this [example repo]().

## License

Peekpoke is distributed under the terms of the [MIT license](https://opensource.org/licenses/MIT). See terms and conditions [here](./LICENSE-MIT)

[crates.io]: https://crates.io/crates/peekpoke
[latest version]: https://img.shields.io/crates/v/peekpoke.svg
[documentation]: https://docs.rs/libc/badge.svg
[docs.rs]: https://docs.rs/peekpoke
[downloads]: https://img.shields.io/crates/d/peekpoke
[license]: https://img.shields.io/crates/l/peekpoke.svg
