#pragma once

extern "C" {
	#include "lua.h"

	#include "lauxlib.h"
	#include "lualib.h"
}

#include <string>
#include <boost/stacktrace.hpp>


void lprint(lua_State *L, std::string s) {
	//luaL_dostring(L, "print('LPRINT')");
	std::string str = "print('" + s + "')";
	luaL_dostring(L, str.c_str());
}


std::string get_stacktrace() {
	boost::stacktrace::stacktrace st;
	st = boost::stacktrace::stacktrace();
	return boost::stacktrace::to_string(st);
}