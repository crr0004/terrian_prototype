triangle = nil
function init()
	triangle = Triangle.create()
--[[	point1 = Point.create(0.0, 0.0, 0.0)
	point2 = Point.create(1.0, 0.0, 0.0)
	point3 = Point.create(0.0, 1.0, 0.0)
	--]]
end

function update()
--[[
	if Mouse.asCollideCircle(1.0).collides(point1.v) then
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
