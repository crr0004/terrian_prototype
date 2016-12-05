HeightmapObject = nil
function init()
	settings = {
		width=20,
		x=10.0,
		y=5.5,
		z=-10.0,
		widthDensity=10
	}
	HeightmapObject = Heightmap.Build(settings)
	HeightmapObject:getSettings()

end
