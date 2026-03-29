require("rtmidi")

for i = 1, 2 do
	local _rtmidi = i == 1 and rtmidi.CreateInput() or rtmidi.CreateOutput()
	local result = {}

	result.current_api = {}
	result.current_api.number = _rtmidi:GetCurrentAPI()
	result.current_api.name = _rtmidi:GetAPIName(result.current_api.number)
	result.current_api.display_name = _rtmidi:GetAPIDisplayName(result.current_api.number)
	result.compiled_api = _rtmidi:GetCompiledAPI()

	result.port_count = _rtmidi:GetPortCount()
	result.ports = {}
	for i = 1, result.port_count do
		result.ports[i] = {}
		result.ports[i].number = i - 1
		result.ports[i].name = _rtmidi:GetPortName(i - 1)
	end

	print(string.format("\n%s", _rtmidi))
	PrintTable(result)
end
