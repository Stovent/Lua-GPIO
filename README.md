# Lua-GPIO
A Lua library to use the GPIO pins of a raspberry pi

# Installation
Clone the repo with `git clone https://github.com/Stovent/Lua-GPIO` %%%
Go into the the folder and execute `sudo make` %%%
The library will be located at `/usr/lib/libLua-GPIO.so` by default. %%%
To change location and name, open `Makefile` and set the `targetPath` and `output` variables, respectively, to where you want to compile the library.

#How to use
load the library with `package.loadlib("/usr/lib/libLua-GPIO.so", "luaopen_luagpio")`. Functions will be accessible with `luagpio.<function name>()`.

#Docs
`initPin(pinNumber, "mode")`: Set pin <pinNumber> to either input or output. If <mode> = "output", pin will be an output. Any other value value will set the pin to input. %%%
`setPin(pinNumber, value)`: If <value> = 0, switch pin <pinNumber> off. Any other value swtich pin <pinNumber> on.
