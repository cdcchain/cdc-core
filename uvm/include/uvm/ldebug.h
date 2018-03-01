/*
** $Id: ldebug.h,v 2.14 2015/05/22 17:45:56 roberto Exp $
** Auxiliary functions from Debug Interface module
** See Copyright Notice in lua.h
*/

#ifndef ldebug_h
#define ldebug_h


#include "uvm/lstate.h"


#define pcRel(pc, p)	(lua_cast(int, (pc) - (p)->code) - 1)

#define getfuncline(f,pc)	(((f)->lineinfo) ? (f)->lineinfo[pc] : -1)

#define resethookcount(L)	(L->hookcount = L->basehookcount)


LUAI_FUNC void luaG_typeerror(lua_State *L, const TValue *o,
    const char *opname);
LUAI_FUNC void luaG_concaterror(lua_State *L, const TValue *p1,
    const TValue *p2);
LUAI_FUNC void luaG_opinterror(lua_State *L, const TValue *p1,
    const TValue *p2,
    const char *msg);
LUAI_FUNC void luaG_tointerror(lua_State *L, const TValue *p1,
    const TValue *p2);
LUAI_FUNC void luaG_ordererror(lua_State *L, const TValue *p1,
    const TValue *p2);
LUAI_FUNC void luaG_runerror(lua_State *L, const char *fmt, ...);
LUAI_FUNC const char *luaG_addinfo(lua_State *L, const char *msg,
    TString *src, int line);
LUAI_FUNC void luaG_errormsg(lua_State *L, const char *msg=nullptr);
LUAI_FUNC void luaG_traceexec(lua_State *L);


#endif
