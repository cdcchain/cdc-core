/*
** $Id: lapi.h,v 2.9 2015/03/06 19:49:50 roberto Exp $
** Auxiliary functions from Lua API
** See Copyright Notice in lua.h
*/

#ifndef lapi_h
#define lapi_h

#include <stdio.h>
#include <string.h>
#include <string>
#include <list>

#include "uvm/llimits.h"
#include "uvm/lstate.h"
#include "uvm/uvm_api.h"

#define api_incr_top(L)   {L->top++; api_check(L, L->top <= L->ci->top, \
				"stack overflow");}

#define adjustresults(L,nres) \
        { if ((nres) == LUA_MULTRET && L->ci->top < L->top) L->ci->top = L->top; }

#define api_checknelems(L,n)	api_check(L, (n) < (L->top - L->ci->func), \
				  "not enough elements in the stack")

/**
 * index -2 is key, index -1 is value
 */
typedef bool (lua_table_traverser)(lua_State *L, void *ud);

typedef bool (lua_table_traverser_with_nested)(lua_State *L, void *ud, size_t len, std::list<const void *> &jsons, size_t recur_depth);

/**
 * traverse visit lua table
 */
size_t luaL_traverse_table(lua_State *L, int index, lua_table_traverser traverser, void *ud);
size_t luaL_traverse_table_with_nested(lua_State *L, int index, lua_table_traverser_with_nested traverser, void *ud, std::list<const void*> &jsons, size_t recur_depth);

/**
 * count size of _G(global variables table)
 */
size_t luaL_count_global_variables(lua_State *L);

/**
 * get global var names of L, store them in param list
 */
void luaL_get_global_variables(lua_State *L, std::list<std::string> *list);


#endif
