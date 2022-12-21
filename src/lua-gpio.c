#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "gpio.h"

static int initPin(lua_State* L)
{
    const int pin = lua_tointeger(L, -2);
    const int func = lua_toboolean(L, -1);

    gpio_init_pin(pin, func);

    fprintf(stdout, "initPin(pin: %d, func: %d)\n", pin, func);

    return 0;
}

static int setPin(lua_State* L)
{
    const int pin = lua_tointeger(L, -2);
    const int val = lua_toboolean(L, -1);

    gpio_set_pin(pin, val);

    fprintf(stdout, "setPin(pin: %d, val: %d)\n", pin, val);

    return 0;
}

static int getPin(lua_State* L)
{
    const int pin = lua_tointeger(L, -1);

    const int value = gpio_get_pin(pin);

    lua_pushboolean(L, value);

    fprintf(stdout, "getPin(pin: %d): %d\n", pin, value);

    return 1;
}

static const struct luaL_Reg luagpio[] = {
    {"initPin", initPin},
    {"setPin", setPin},
    {"getPin", getPin},
    {NULL, NULL},
};

int luaopen_luagpio(lua_State* L)
{
    if(gpio_init())
    {
        luaL_openlib(L, "luagpio", luagpio, 0);
    }
    return 1;
}
