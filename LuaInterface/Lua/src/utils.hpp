#pragma once

extern "C" {
	#include "lua.h"

	#include "lauxlib.h"
	#include "lualib.h"
}

#include <string>

void lprint(lua_State *L, std::string s) {
	std::string str = "print('" + s + "')";
	luaL_dostring(L, str.c_str());
}