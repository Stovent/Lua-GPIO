# Lua-GPIO
A Lua library to use the GPIO pins of a raspberry pi

# Installation
Clone the repo with `git clone https://github.com/Stovent/Lua-GPIO` \
Go into the the folder and install the dependencies with `sudo apt install liblua5.1-0-dev`

Compile and install the library with
```sh
make
sudo make install
```

The library will be located at `/usr/lib/libLua-GPIO.so` by default. \
To change location and name, open `Makefile` and set the `installDir` and `libName` variables, respectively, to where you want to compile the library.

# How to use
load the library with `package.loadlib("/usr/lib/libLua-GPIO.so", "luaopen_luagpio")()`. Functions will be accessible with `luagpio.<function name>()`. \
The pin numbers are the BCM numbers. Check `https://pinout.xyz/` for number reference

# Docs
`initPin(pinNumber, mode)`: Set pin to either input or output. If `mode` = 0, pin will be an input. Any other value value will set the pin to output. \
`setPin(pinNumber, value)`: If `value` = 0, switch pin off. Any other value switch pin <pinNumber> on.
