require("rtmidi")

local result = {}

result.compiled_api = {}
for i, api in ipairs(rtmidi.GetCompiledAPI()) do
	result.compiled_api[i] = {}
	result.compiled_api[i].number = api
	result.compiled_api[i].name = rtmidi.GetAPIName(api)
	result.compiled_api[i].display_name = rtmidi.GetAPIDisplayName(api)
end

print("\nrtmidi")
PrintTable(result)

for i = 1, 2 do
	local _rtmidi = i == 1 and rtmidi.CreateInput() or rtmidi.CreateOutput()
	local result = {}

	result.current_api = {}
	result.current_api.number = _rtmidi:GetCurrentAPI()
	result.current_api.name = rtmidi.GetAPIName(result.current_api.number)
	result.current_api.display_name = rtmidi.GetAPIDisplayName(result.current_api.number)

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
