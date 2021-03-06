/** \file
 * \brief iupval Binding for Lua.
 *
 * See Copyright Notice in iup.h
 * $Id: luaval.h,v 1.3 2003/06/17 22:05:03 scuri Exp $
 */
 
#ifndef __LUAVAL_H 
#define __LUAVAL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LUA_NOOBJECT  /* Lua 3 */
int vallua_open (void);
#endif

#ifdef LUA_NOREF  /* Lua 4 or 5 */
void vallua_open (lua_State * L);
#endif

#ifdef __cplusplus
}
#endif

#endif
