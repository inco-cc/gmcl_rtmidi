/* See LICENSE file for copyright and license details. */

#include <map>
#include "GarrysMod/Lua/Interface.h"

extern std::map<int, const char*> messageName;
extern std::map<int, const char*> messageTypeName;

extern int GetMessageName(lua_State*);
extern int GetMessageTypeName(lua_State*);
extern int GetMessageType(lua_State*);
extern int GetMessageChannel(lua_State*);
