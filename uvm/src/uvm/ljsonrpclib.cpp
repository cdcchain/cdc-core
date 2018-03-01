#define ljsonrpclib_cpp

#include "uvm/lprefix.h"


#include <errno.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <memory>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "uvm/lua.h"

#include "uvm/lauxlib.h"
#include "uvm/lualib.h"
#include "uvm/uvm_api.h"

#undef LUA_JSONRPC_VERSION
#define LUA_JSONRPC_VERSION "1.0"

// TODO

static const luaL_Reg jsonrpclib[] = {
	// { "listen", lualib_http_listen },
	{ "version", nullptr },
	{ nullptr, nullptr }
};


LUAMOD_API int luaopen_jsonrpc(lua_State *L) {
	luaL_newlib(L, jsonrpclib);
	lua_pushstring(L, LUA_JSONRPC_VERSION);
	lua_setfield(L, -2, "version");
	return 1;
}
