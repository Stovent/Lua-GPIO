# Lua-GPIO
A Lua library to use the GPIO pins of a Raspberry Pi.

It only works on Raspberry Pi with Raspberry Pi OS (Raspbian).

This library only supports setting the GPIO pins as input and output, it does not support the alternative functions yet (SPI, UART, ...).

It has been benchmarked on a Raspberry Pi 3 B and an oscilloscope, the GPIO C code reached 6Mhz toggles (pin on/pin off), and Lua code reached 1Mhz toggles.

## Install
Clone the repo with `git clone https://github.com/Stovent/Lua-GPIO`.

Go into the the folder and install the dependencies with `sudo apt install liblua5.2-dev`.
The minimal supported Lua version is 5.2.

Compile and install the library with
```sh
make
sudo make install
```

The library will be installed at `/usr/local/lib/libLua-GPIO.so` by default.
To change the directory and name, open `Makefile` and set the `installDir` and `libName` variables respectively.

Uninstall the library with
```sh
sudo make uninstall
```

## How to use
Load the library with `luagpio = package.loadlib("/usr/local/lib/libLua-GPIO.so", "luaopen_luagpio")()`. Functions will be accessible with `luagpio.<function name>()`.

The pin numbers are the BCM numbers. Check `https://pinout.xyz/` for number reference (GPIO 0-27).

## Docs
`initPin(pinNumber, mode)`: Set pin to either input or output. If `mode = false`, pin will be an input. true will set the pin to output.

`setPin(pinNumber, value)`: If `value = false`, switch pin off. true will switch the pin on.

`getPin(pinNumber)`: Returns true if the pin is set, false otherwise.
