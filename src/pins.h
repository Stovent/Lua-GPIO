#ifndef PINS_H
#define PINS_H

#include <lua.h>

int initPin(lua_State* L);
int setPin(lua_State* L);
int getPin(lua_State* L);

#endif // PINS_H
