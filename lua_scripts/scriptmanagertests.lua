function callLib()
	MockClass.noParams()
end
function callLibParams()
	MockClass.withParam("is this printed?")
end
function callLibReturn()
	local value = MockClass.withReturn()
end
function callLibTableReturn()
	tableReturned = MockClass.withTableReturn()
end
