#Internal API for working with LUA

##Sandboxing
- Have to create a copy of the inititional environment
- Then set that that as first upvalue of script (_ENV)
- Then reset the global to that
##Exposing heightmap
- Heightmap properties are exposed
- Build is triggered from script
- Script isn't responsible for keeping memory/reference


###Potential flow
1. Program and context is loaded
2. Script is loaded
3. If script contains update(delta), it wants physics/logic tick
4. Otherwise script is executed as is.
5. Singleton is exposed to all scripts to manage heightmap/polygon objects
