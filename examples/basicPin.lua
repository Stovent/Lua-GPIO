 -- load the library. Functions are accessible via luagpio.<function name>()
local lib = assert(package.loadlib("/usr/lib/libLua-GPIO.so", "luaopen_luagpio"))
lib()

luagpio.initPin(17, true) -- set the pin to output

luagpio.setPin(17, true) -- switch on the pin

os.execute("sleep 1") -- Pause for 1 second

luagpio.setPin(17, false) -- Switch off the pin
