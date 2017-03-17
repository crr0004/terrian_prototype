triangle = nil
function init()
	triangle = Triangle.Create()
	triangle1 = Triangle.Create()
	triangle1:translate({5.0,0.0,0.0})
	for k,v in ipairs(triangle1:v3()) do print(v) end
--[[	point1 = Point.create(0.0, 0.0, 0.0)
	point2 = Point.create(1.0, 0.0, 0.0)
	point3 = Point.create(0.0, 1.0, 0.0)
	--]]
end

function update()
	--triangle:v1({-math.sin(os.clock() * 10) * 10, 0.0, 0.0})
	triangle:v2({1.0, 0.0, 0.0})
	triangle:v3({1.0, 1.0, 0.0})
	mouseCords = Mouse.asCollideCircle(1.0, {0.0, 0.0, 0.0})
	triangle:v1(mouseCords)
	print(mouseCords[1])
	print(mouseCords[2])
	print(mouseCords[3])
	--triangle:translate({-5.0,0.0,0.0})
--[[
	if Mouse.asCollideCircle(1.0, point1.v) then
		point1.v = Mouse.getV()
	end
	if Mouse.asCollideCircle(1.0).collides(point2.v) then
		point2.v = Mouse.getV()
	end
	if Mouse.asCollideCircle(1.0).collides(point3.v) then
		point3.v = Mouse.getV()
	end
	triangle.v1 = point1.v
	triangle.v2 = point2.v
	triangle.v3 = point3.v
	--]]
end
