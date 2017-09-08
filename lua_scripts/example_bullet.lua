triangle = nil
p1 = {-1.0, 0.0, 0.0}
p2 = {0.0, 0.0, 0.0}
p3 = {0.0, 1.0, 0.0}
function init()
	triangle = Triangle.Create()
	triangle1 = Triangle.Create()
	triangle1:translate({5.0,0.0,0.0})
	triangle:translate({-7.0,0.0,0.0})
--	for k,v in ipairs(triangle1:v3()) do print(v) end
--[[	point1 = Point.create(0.0, 0.0, 0.0)
	point2 = Point.create(1.0, 0.0, 0.0)
	point3 = Point.create(0.0, 1.0, 0.0)
	--]]
end

function update()

end
