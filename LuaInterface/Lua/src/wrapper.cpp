#include <stdlib.h>

#define lmathlib_c
#define LUA_LIB

extern "C" {
	#include "lua.h"

	#include "lauxlib.h"
	#include "lualib.h"
}

#include <dlib/dnn.h>
#include <iostream>
#include <dlib/data_io.h>

using namespace std;
using namespace dlib;


/*
** Expects: 1 param
*/
static int wrapper_square(lua_State *L) {
	printf("C - wrapper_square"); // printf DOESN NOT WORK from inside the lua core
	float ret = luaL_checknumber(L, 1);
	lua_pushnumber(L, ret*ret);
	return 1;
}


/*
** Expects: 0 params
*/
static int wrapper_dlib_example(lua_State *L) {
	// based on http://dlib.net/dnn_introduction_ex.cpp.html

	using net_type = loss_multiclass_log<
		fc<1,
		relu<fc<2,
		input<matrix<unsigned char>>
		>>>>;

	// So with that out of the way, we can make a network instance.
	net_type net;
	// And then train it using the MNIST data.  The code below uses mini-batch stochastic
	// gradient descent with an initial learning rate of 0.01 to accomplish this.
	dnn_trainer<net_type> trainer(net);
	trainer.set_learning_rate(0.01);
	trainer.set_min_learning_rate(0.00001);
	trainer.set_mini_batch_size(1);
	trainer.be_verbose();

	const std::vector<std::vector<int>> in = { {0,0}, {1,0}, {0,1}, {1,1} };
	const std::vector<int> out = { 0, 1, 1, 0 };
	//trainer.train(&in, &out);



	return 0;
}



/*
** List wrapper functions to be exposed to lua
*/
static const luaL_Reg wrapperlib[] = {
	{ "square",   wrapper_square },
    { "dlib_example", wrapper_dlib_example },
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




