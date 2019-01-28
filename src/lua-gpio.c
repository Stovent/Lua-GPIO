#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include "pins.h"

#define BASE 0x20200000

uint32_t* gpio;

static void initLib()
{
    int fd;
    if((fd = open("/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC)) == 0)
    {
        printf("Could not open /dev/gpiomem\n");
        return;
    }

    if((gpio = (uint32_t*)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, BASE)) == MAP_FAILED)
    {
        printf("Could not map gpio memory: %s\n", strerror(errno));
        return;
    }
    printf("Lua-GPIO initialized\n");
}

static const struct luaL_Reg luagpio[] = {
    {"initPin", initPin},
    {"setPin", setPin},
    {"getPin", getPin},
    {NULL, NULL}
};

int luaopen_luagpio(lua_State* L)
{
    initLib();
    luaL_openlib(L, "luagpio", luagpio, 0);
    return 1;
}
