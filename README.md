# Terrian Prototype
A prototype for creating a terrian &amp; heightmap.

# Building
Uses CMake for build system.

Currently building on Fedora and Windows (MSVC).

## To Be Built On In The Future:
- mingw (Windows and cross compile)
- cygwin
- Mac OSX (when I get a system to)
- Possibly Nintedo 3ds

Depends on GLFW3, glm, bullet3 and c++11.

You need to build bullet3 on windows first. I will eventually add it to build in source so you don't have to.

Uses GLAD, is built in source

[Lua](https://github.com/LuaDist/lua/tree/5.2.4) is built in source using submodules

[Lua Manual](https://www.lua.org/manual/5.2/)

Tests suite uses [Catch](https://github.com/philsquared/Catch/tree/v1.2.1). It's header only and included in the repo

# Fedora 23
I think these names are wrong.

		dnf -y install glew-devel glfw-devel glm-devel

# Example Screenshots
[Examples folder link](https://github.com/crr0004/terrian_prototype/tree/master/examples)

## Basic Example
Shows how to setup a basic window, see basic.cpp in [examples folder link](https://github.com/crr0004/terrian_prototype/tree/master/examples)

<img width=512 height=407 src="https://i.imgur.com/1Z33NwC.png"></img>

## Bullet Collision Example - WIP
A WIP shows how to use bullet with existing systems. An example of how to use bullet's collision system. See bullet_collision.cpp in [examples folder link](https://github.com/crr0004/terrian_prototype/tree/master/examples)

<img width=512 height=230 src="https://i.imgur.com/Zt7lSuv.png"></img>

## Bullet Example
An example that uses bullet's dynamics system and my rendering system. See bullet.cpp in [examples folder link](https://github.com/crr0004/terrian_prototype/tree/master/examples)

<img width=512 height=407 src="https://i.imgur.com/u6PJm7P.png"></img>

## Bullet Intergration Example - WIP
An example that shows how I might be intergrating bullet into my existing system. See bullet_integration in [examples folder link](https://github.com/crr0004/terrian_prototype/tree/master/examples).

<img width=512 height=407 src="https://i.imgur.com/bJit09L.png"></img>

## One Example
An example that shows using lua scripts to interact with the engine. Uses triangle_drawing.lua script in lua_scripts. See one.cpp in [examples folder link](https://github.com/crr0004/terrian_prototype/tree/master/examples).

<img width=512 height=283 src="https://i.imgur.com/WrUsRr0.png"/>


