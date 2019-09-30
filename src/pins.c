#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "pins.h"

extern uint32_t* gpio;

const int fselShift[] = {
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27
};

const int fsel[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

const int set[] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};

const int setShift[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21
};

const int clr[] = {
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11
};

const int* clrShift = setShift;

const int lvl[] = {
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14
};

const int* lvlShift = setShift;

int initPin(lua_State* L)
{
    int pin = lua_toboolean(L, 1);
    const char* func = lua_tostring(L, 2);

    *(gpio + fsel[pin]) &= ~(1 << fselShift[pin]);

    if(strcmp(func, "output") == 0)
    {
        *(gpio + fsel[pin]) |= (1 << fselShift[pin]);
    }
    else
    {
        *(gpio + fsel[pin]) |= (0 << fselShift[pin]);
    }

    fprintf(stdout, "Pin %d set to %s\n", pin, func);

    return 0;
}

int setPin(lua_State* L)
{
    int pin = lua_toboolean(L, 1);
    int val = lua_toboolean(L, 2);

    fprintf(stdout, "Requested pin %d to be at value %d\n", pin, val);

    if(val)
    {
        *(gpio + set[pin]) &= ~(1 << setShift[pin]);
        *(gpio + set[pin]) |=  (1 << setShift[pin]);
    }
    else
    {
        *(gpio + clr[pin]) &= ~(1 << clrShift[pin]);
        *(gpio + clr[pin]) |=  (1 << clrShift[pin]);
    }

    return 0;
}

int getPin(lua_State* L)
{
    int pin = lua_tonumber(L, 1);
    int value;

    if(*(gpio + lvl[pin]) & (1 << lvlShift[pin]))
        value = 1;
    else
        value = 0;

    lua_pushboolean(L, value);

    fprintf(stdout, "Get pin %d, value %d\n", pin, value);

    return 1;
}
