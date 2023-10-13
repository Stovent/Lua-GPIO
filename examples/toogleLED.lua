 -- load the library. Functions are accessible via luagpio.<function name>()
luagpio = assert(package.loadlib("/usr/local/lib/libLua-GPIO.so", "luaopen_luagpio"))()

luagpio.initPin(17, true) -- set the pin to output

while true do
    luagpio.setPin(17, true) -- switch on the pin

    os.execute("sleep 1") -- Pause for 1 second

    luagpio.setPin(17, false) -- Switch off the pin

    os.execute("sleep 1") -- Pause for 1 second
end
