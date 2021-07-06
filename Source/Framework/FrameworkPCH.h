#pragma once

#ifdef _WINDOWS 
#include <Windows.h>
#endif

#include <assert.h>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../ProjectConfig.h"


typedef std::function<void(double)>                                       GameLoopFunc;
typedef std::function<void(const class Renderer&)>                        GameDrawFunc;
typedef std::function<void(int key, int scancode, int action, int mode)> GameInputFunc;
typedef std::function<void(double x, double y)>                      GameCursorPosFunc;


#include <Constants.h>
#include <Debug/Debugging.h>
#include <Debug/Logger.h>

#include <Utilities/Utilities.h>
#include <Utilities/ColorList.h>

#include <GameClass.h>

#include <Application.h>
#include <AppInitializer.h>

#include <Graphics/ShaderProgram.h>
#include <Graphics/Mesh.h>
#include <Graphics/Renderer.h>
#include <Graphics/Shape.h>
