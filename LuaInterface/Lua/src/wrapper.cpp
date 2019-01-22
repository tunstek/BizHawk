#include <stdlib.h>

#define lmathlib_c
#define LUA_LIB

extern "C" {
	#include "lua.h"

	#include "lauxlib.h"
	#include "lualib.h"
}




static int wrapper_square(lua_State *L) {
	printf("C - wrapper_square");
	float ret = luaL_checknumber(L, 1);
	lua_pushnumber(L, ret*ret);
	return 1;
}




/*
** List wrapper functions to be exposed to lua
*/
static const luaL_Reg wrapperlib[] = {
	{ "square",   wrapper_square },
	{ NULL, NULL }
};


/*
** Open wrapper library
*/
extern "C" {
	LUALIB_API int luaopen_wrapper(lua_State *L) {
		luaL_register(L, LUA_WRAPPERLIBNAME, wrapperlib);
		return 1;
	}
}




