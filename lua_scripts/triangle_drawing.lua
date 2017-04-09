triangle = nil
p1 = {-1.0, 0.0, 0.0}
p2 = {0.0, 0.0, 0.0}
p3 = {0.0, 1.0, 0.0}
function init()
	triangle = Triangle.Create()
	triangle1 = Triangle.Create()
	triangle1:translate({5.0,0.0,0.0})
	triangle:translate({-7.0,0.0,0.0})
	for k,v in ipairs(triangle1:v3()) do print(v) end
--[[	point1 = Point.create(0.0, 0.0, 0.0)
	point2 = Point.create(1.0, 0.0, 0.0)
	point3 = Point.create(0.0, 1.0, 0.0)
	--]]
end

function update()
	mouseCords = Mouse.mouseCords()
	triangle:v2({0.0,-math.sin(os.clock() * 10) * 10,0.0})
	triangle:v3({1.0, 1.0, 0.0})
	if Mouse.getLeftMouseButton() == 1 then
		triangle:v1(mouseCords)
	end
	--local vertexIndex = Collision.GetPointFromRay(triangle:getCollision(), mouseCords)
	--[[	
	var distance = Math.sqrt((point.x - sphere.x) * (point.x - sphere.x) +
	(point.y - sphere.y) * (point.y - sphere.y) +
	(point.z - sphere.z) * (point.z - sphere.z));
	]]--
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
