# Terrian Prototype
A prototype for creating a terrian &amp; heightmap.

#Building
Uses CMake for build system.

Currently building on Fedora and Windows (MSVC).

##To Be Built On In The Future:
- mingw (Windows and cross compile)
- cygwin
- Mac OSX (when I get a system to)
- Possibly Nintedo 3ds

Depends on GLFW3, glm

Uses GLAD, is built in source

[Lua](https://github.com/LuaDist/lua/tree/5.2.4) is built in source using submodules

[Lua Manual](https://www.lua.org/manual/5.2/)

Tests suite uses [Catch](https://github.com/philsquared/Catch/tree/v1.2.1). It's header only and included in the repo

#Fedora 23
I think these names are wrong.

		dnf -y install glew-devel glfw-devel glm-devel
