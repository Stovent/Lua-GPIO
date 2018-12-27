package.loadlib("/usr/lib/libLua-GPIO.so", "luaopen_luagpio")() -- load the library. Functions are accessible via luagpio.<function name>()

luagpio.initPin(17, "output") -- set the pin to output

luagpio.setPin(17, 1) -- switch on the pin

os.execute("sleep 1") -- Pause for 1 second

luagpio.setPin(17, 0) -- Switch off the pin
