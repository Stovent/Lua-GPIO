 -- load the library. Functions are accessible via luagpio.<function name>()
local lib = assert(package.loadlib("/usr/lib/libLua-GPIO.so", "luaopen_luagpio"))
lib()

luagpio.initPin(27, false) -- set the pin to input

while true do
    local value = luagpio.getPin(27) -- get pin value
    print("                            ", value)
end
