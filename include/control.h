/* See LICENSE file for copyright and license details. */

#include <map>
#include "GarrysMod/Lua/Interface.h"

extern std::map<int, const char*> controlName;

extern int GetControlName(lua_State*);
extern int GetControlBitSignificance(lua_State*);
