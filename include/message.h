/* See LICENSE file for copyright and license details. */

#include <map>
#include "GarrysMod/Lua/Interface.h"

extern std::map<int, const char*> messageName;

extern int GetMessageName(lua_State*);
