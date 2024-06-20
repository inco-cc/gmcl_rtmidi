/* See LICENSE file for copyright and license details. */

#include "GarrysMod/Lua/Interface.h"

GMOD_MODULE_OPEN()
{
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->CreateTable();
    LUA->SetField(-2, "rtmidi");

    return 0;
}

GMOD_MODULE_CLOSE()
{
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->PushNil();
    LUA->SetField(-2, "rtmidi");

    return 0;
}
