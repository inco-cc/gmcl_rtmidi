require("rtmidi")

local events = {
	"ShouldOpenMIDIInputPort",
	"OnMIDIInputPortOpened",
	"ShouldCloseMIDIInputPort",
	"OnMIDIInputPortClosed",
	"ShouldOpenMIDIOutputPort",
	"OnMIDIOutputPortOpened",
	"ShouldCloseMIDIOutputPort",
	"OnMIDIOutputPortClosed",
	"ShouldSendMIDIMessage",
	"OnMIDIMessageSent",
	"ShouldReceiveMIDIMessage",
	"OnMIDIMessageReceived",
}

for i, event in ipairs(events) do
	hook.Add(event, "rtmidi_test", function(...)
		print(event, ...)		
	end)
end

for key, value in pairs(rtmidi) do
	if isfunction(value) then
		concommand.Add("rtmidi_" .. key, function(player, command, arguments)
			print(value(unpack(arguments)))
		end)
	end
end
