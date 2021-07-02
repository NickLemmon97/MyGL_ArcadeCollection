#pragma once

#ifdef _WINDOWS 
#include <Windows.h>
#endif

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../ProjectConfig.h"

#include <Constants.h>
#include <Debug/Debugging.h>
#include <Debug/Logger.h>

#include <Utilities/Utilities.h>

#include <GameClass.h>

#include <Application.h>
#include <AppInitializer.h>

#include <Graphics/ShaderProgram.h>
#include <Graphics/Mesh.h>
#include <Graphics/Renderer.h>
