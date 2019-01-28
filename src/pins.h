#ifndef PINS_H
#define PINS_H

#include <lua.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

int initPin(lua_State* L);
int setPin(lua_State* L);
int getInt(lua_State* L);

#endif // PINS_H
