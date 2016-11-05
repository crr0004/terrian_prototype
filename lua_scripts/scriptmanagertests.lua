function callLib()
	MockClass.noParams()
end
function callLibParams()
	MockClass.withParam("is this printed?")
end
function callLibReturn()
	print("Does this return anything?" .. MockClass.withReturn())
end
function callLibTableReturn()
	tableReturned = MockClass.withTableReturn()
	print(tableReturned.name)
end
