#define lmathlib_c
#define LUA_LIB

extern "C" {
	#include "lua.h"

	#include "lauxlib.h"
	#include "lualib.h"
}

#include <stdlib.h>
#include <iostream>

//#include "dlib_test.h"

#include "utils.hpp"
//#include "test.hpp"

using namespace std;


// *** PRINTF DOES NOT WORK FROM THE CORE, EVEN IN C ***
// *** BEST WORKAROUND WOULD BE TO RETURN THE STRING I WANT TO PRINT AND PRINT FROM LUA, pretty annoying though.. ***


static int wrapper_return_string_test(lua_State *L) {
	char* s = "This is a C string";
	lua_pushstring(L, s);
	return 1;
}
static int wrapper_return_array_test(lua_State *L) {
	int arr[] = { 15, 11, 13, 40, 53 };

	lua_newtable(L);
	for (int i = 0; i < 5; i++)
	{
		lua_pushinteger(L, arr[i]);
		lua_rawseti(L, -2, i + 1);
	}
	return 1;
}




static int wrapper_square(lua_State *L) {
	float ret = luaL_checknumber(L, 1);
	lua_pushnumber(L, ret*ret);
	return 1;
}



/*
static int wrapper_dlib_example(lua_State *L) {

	std::vector<float> predictions = dlib_example();
	lua_newtable(L);
	for (int i = 0; i < predictions.size(); i++)
	{
		lua_pushinteger(L, predictions[i]);
		lua_rawseti(L, -2, i + 1);
	}
	
	return 1;
}
*/



/*
** List wrapper functions to be exposed to lua
*/
static const luaL_Reg wrapperlib[] = {
	{ "square",   wrapper_square },
	{ "return_string_test", wrapper_return_string_test },
	{ "return_array_test", wrapper_return_array_test },
    //{ "dlib_example", wrapper_dlib_example },
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




