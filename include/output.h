/* See LICENSE file for copyright and license details. */

#include <map>
#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"

extern RtMidiOut *mainOutput;

extern std::map<unsigned int, RtMidiOut*> portOutput;

extern int GetOutputPortCount(lua_State*);
extern int GetOutputPortName(lua_State*);
extern int IsOutputPortOpen(lua_State*);
extern int CloseOutputPort(lua_State*);
extern int OpenOutputPort(lua_State*);
extern int SendMessage(lua_State*);
