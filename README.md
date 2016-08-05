# TywyllEngine
OpenGL Game Engine  that will work in the future... maybe... when will fix problems with architecture and renderer.......

#How To Build
Currently works only under Visual Studio 2015 version.
Run cmake and make build folder to Build.


#Is it still in development?
Sadly, but not. Due to a lot of problems and stupid decisions, I decided to refactor everything. Well, almost everything. The worst part is the Renderer API, which does not work properly and do not heave needed features. Due to this, decided to stop working on engine and start working on Renderer API.

#What is the current progress of Renderer API
The Renderer API will be using Vulkan API and it is currently under development. Will be posted on different repository.

#Anything works on current Renderer API?
Yup, for example:
- Wavefront file rendering (works just with v,n,uv)
- MD5 Skeletal animation rendering
- Font rendering
- ImgGui
- There are more things that do not work as the amount of things that work...

#ThirdParty libraries used
> - Bullet3 - For Physics
> - FreeType - For font rendering
> - Glew - OpenGL
> - Glm - For Math but not used in this engine as I have my own math library (worst mistake I ever did in my life......)
> - Lua - For running Lua Script
> - LuaSol2 - For running LuaScript (it uses Lua)
> - TinyXml2 - For Xml Parsing
> - Zlib - the name says it all

#Credits
Thanks to the authors of these books:
- Game Engine Architecture
- Game Code Complete 4
- Game Programming Patterns



