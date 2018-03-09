/*
** $Id: lopcodes.c,v 1.55 2015/01/05 13:48:33 roberto Exp $
** Opcodes for Lua virtual machine
** See Copyright Notice in lua.h
*/

#define lopcodes_cpp
#define LUA_CORE

#include "uvm/lprefix.h"


#include <stddef.h>

#include "uvm/lopcodes.h"


/* ORDER OP */

LUAI_DDEF const char *const luaP_opnames[UNUM_OPCODES + 1] = {
    "MOVE",
    "LOADK",
    "LOADKX",
    "LOADBOOL",
    "LOADNIL",
    "GETUPVAL",
    "GETTABUP",
    "GETTABLE",
    "SETTABUP",
    "SETUPVAL",
    "SETTABLE",
    "NEWTABLE",
    "SELF",
    "ADD",
    "SUB",
    "MUL",
    "MOD",
    "POW",
    "DIV",
    "IDIV",
    "BAND",
    "BOR",
    "BXOR",
    "SHL",
    "SHR",
    "UNM",
    "BNOT",
    "NOT",
    "LEN",
    "CONCAT",
    "JMP",
    "EQ",
    "LT",
    "LE",
    "TEST",
    "TESTSET",
    "CALL",
    "TAILCALL",
    "RETURN",
    "FORLOOP",
    "FORPREP",
    "TFORCALL",
    "TFORLOOP",
    "SETLIST",
    "CLOSURE",
    "VARARG",
    "EXTRAARG",
    nullptr
};


#define opmode(t,a,b,c,m) (((t)<<7) | ((a)<<6) | ((b)<<4) | ((c)<<2) | (m))

LUAI_DDEF const lu_byte luaP_opmodes[UNUM_OPCODES] = {
    /*       T  A    B       C     mode		   opcode	*/
    opmode(0, 1, OpArgR, OpArgN, iABC)		/* UOP_MOVE */
    , opmode(0, 1, OpArgK, OpArgN, iABx)		/* UOP_LOADK */
    , opmode(0, 1, OpArgN, OpArgN, iABx)		/* UOP_LOADKX */
    , opmode(0, 1, OpArgU, OpArgU, iABC)		/* UOP_LOADBOOL */
    , opmode(0, 1, OpArgU, OpArgN, iABC)		/* UOP_LOADNIL */
    , opmode(0, 1, OpArgU, OpArgN, iABC)		/* UOP_GETUPVAL */
    , opmode(0, 1, OpArgU, OpArgK, iABC)		/* UOP_GETTABUP */
    , opmode(0, 1, OpArgR, OpArgK, iABC)		/* UOP_GETTABLE */
    , opmode(0, 0, OpArgK, OpArgK, iABC)		/* UOP_SETTABUP */
    , opmode(0, 0, OpArgU, OpArgN, iABC)		/* UOP_SETUPVAL */
    , opmode(0, 0, OpArgK, OpArgK, iABC)		/* UOP_SETTABLE */
    , opmode(0, 1, OpArgU, OpArgU, iABC)		/* UOP_NEWTABLE */
    , opmode(0, 1, OpArgR, OpArgK, iABC)		/* UOP_SELF */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_ADD */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_SUB */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_MUL */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_MOD */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_POW */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_DIV */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_IDIV */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_BAND */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_BOR */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_BXOR */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_SHL */
    , opmode(0, 1, OpArgK, OpArgK, iABC)		/* UOP_SHR */
    , opmode(0, 1, OpArgR, OpArgN, iABC)		/* UOP_UNM */
    , opmode(0, 1, OpArgR, OpArgN, iABC)		/* UOP_BNOT */
    , opmode(0, 1, OpArgR, OpArgN, iABC)		/* UOP_NOT */
    , opmode(0, 1, OpArgR, OpArgN, iABC)		/* UOP_LEN */
    , opmode(0, 1, OpArgR, OpArgR, iABC)		/* UOP_CONCAT */
    , opmode(0, 0, OpArgR, OpArgN, iAsBx)		/* UOP_JMP */
    , opmode(1, 0, OpArgK, OpArgK, iABC)		/* UOP_EQ */
    , opmode(1, 0, OpArgK, OpArgK, iABC)		/* UOP_LT */
    , opmode(1, 0, OpArgK, OpArgK, iABC)		/* UOP_LE */
    , opmode(1, 0, OpArgN, OpArgU, iABC)		/* UOP_TEST */
    , opmode(1, 1, OpArgR, OpArgU, iABC)		/* UOP_TESTSET */
    , opmode(0, 1, OpArgU, OpArgU, iABC)		/* UOP_CALL */
    , opmode(0, 1, OpArgU, OpArgU, iABC)		/* UOP_TAILCALL */
    , opmode(0, 0, OpArgU, OpArgN, iABC)		/* UOP_RETURN */
    , opmode(0, 1, OpArgR, OpArgN, iAsBx)		/* UOP_FORLOOP */
    , opmode(0, 1, OpArgR, OpArgN, iAsBx)		/* UOP_FORPREP */
    , opmode(0, 0, OpArgN, OpArgU, iABC)		/* UOP_TFORCALL */
    , opmode(0, 1, OpArgR, OpArgN, iAsBx)		/* UOP_TFORLOOP */
    , opmode(0, 0, OpArgU, OpArgU, iABC)		/* UOP_SETLIST */
    , opmode(0, 1, OpArgU, OpArgN, iABx)		/* UOP_CLOSURE */
    , opmode(0, 1, OpArgU, OpArgN, iABC)		/* UOP_VARARG */
    , opmode(0, 0, OpArgU, OpArgU, iAx)		/* UOP_EXTRAARG */
};

