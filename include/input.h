/* See LICENSE file for copyright and license details. */

#include <map>
#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"

extern RtMidiIn *mainInput;

extern std::map<unsigned int, RtMidiIn*> portInput;

extern int GetInputPortCount(lua_State*);
extern int GetInputPortName(lua_State*);
extern int IsInputPortOpen(lua_State*);
extern int CloseInputPort(lua_State*);
extern int OpenInputPort(lua_State*);
extern int ReceiveMessage(lua_State*);
