require("rtmidi")

local rtmidi_in = rtmidi.CreateInput()
print(string.format("Created: %s", rtmidi_in))
local port_count = rtmidi_in:GetPortCount()
print(string.format("Number of ports for %s: %i", rtmidi_in, port_count))
for port = 0, port_count - 1 do
	print(string.format("Name of port %i for %s: %s", port, rtmidi_in, rtmidi_in:GetPortName(port)))
end

local rtmidi_out = rtmidi.CreateOutput()
print(string.format("Created: %s", rtmidi_out))
port_count = rtmidi_out:GetPortCount()
print(string.format("Number of ports for %s: %i", rtmidi_out, port_count))
for port = 0, port_count - 1 do
	print(string.format("Name of port %i for %s: %s", port, rtmidi_out, rtmidi_out:GetPortName(port)))
end
