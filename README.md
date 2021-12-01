# My OpenGL Framework
An in progress framework to practice OpenGL and framework setup with the intent to make small games. 
A comfortable environment for me to create what I want in the way I want to.  There are a lot of changes being made since it is in progress and there
may even be some left over code from a completely different iteration.

# Arcade Collection
My first set of games made using this framework involves a set of Arcade style games such as asteroids, death race among other classics planned.
I think the best way to know what I want to use from a framework comes from trying to make a game using it.
I am adding components as I need them

# Building
Requires Premake5 (I have put it in my environment variables, you may need to download it)
run PremakeGenerateBuildFiles.bat to generate a vs2019 project

# Build Note
The current state of the project assumes vs2019. 
There is an issue copying over the dlls that generated since the Game folder doesn't exist
The supplied dlls and libs are only compatible with vs2019, as that is how I am creating the project

# Licenses

## Included external libraries (packed in)

| Library    | Licence                                                                           | Web page                                |
| ---------- | --------------------------------------------------------------------------------- | --------------------------------------- |
| GLM        | [MIT/Happy Bunny](https://github.com/g-truc/glm/blob/master/copying.txt)          | https://github.com/g-truc/glm           |
| GLFW 3     | [zlib/libpng](https://github.com/glfw/glfw/blob/master/LICENSE.md)                | https://github.com/glfw/glfw            |
| GLEW       | | |

------
