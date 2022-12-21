# Lua-GPIO
A Lua library to use the GPIO pins of a Raspberry Pi.

This library only supports setting the GPIO pins as input and output. It does not support the alternative functions yet (SPI, UART, ...).

It only works on Raspberry Pi with the Raspberry Pi OS (Raspbian).

## Install
Clone the repo with `git clone https://github.com/Stovent/Lua-GPIO`.
Go into the the folder and install the dependencies with `sudo apt install liblua5.1-0-dev`.

Compile and install the library with
```sh
make
sudo make install
```

The library will be installed at `/usr/lib/libLua-GPIO.so` by default.
To change the directory and name, open `Makefile` and set the `installDir` and `libName` variables respectively.

## How to use
Load the library with `package.loadlib("/usr/lib/libLua-GPIO.so", "luaopen_luagpio")()`. Functions will be accessible with `luagpio.<function name>()`.

The pin numbers are the BCM numbers. Check `https://pinout.xyz/` for number reference (GPIO 0-27).

## Docs
`initPin(pinNumber, mode)`: Set pin to either input or output. If `mode = false`, pin will be an input. true will set the pin to output.

`setPin(pinNumber, value)`: If `value = false`, switch pin off. true will switch the pin on.

`getPin(pinNumber)`: Returns true if the pin is set, false otherwise.
