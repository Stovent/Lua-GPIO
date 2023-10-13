 -- load the library. Functions are accessible via luagpio.<function name>()
luagpio = assert(package.loadlib("/usr/local/lib/libLua-GPIO.so", "luaopen_luagpio"))()

luagpio.initPin(27, false) -- set the pin to input

while true do
    local value = luagpio.getPin(27) -- get pin value
    print("                            ", value)
end
