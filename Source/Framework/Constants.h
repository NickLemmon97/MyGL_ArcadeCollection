#pragma once

//Constants
static const char* APP_TITLE = "OpenGL Shapes";

constexpr int INITIAL_WINDOW_HEIGHT = 720;
constexpr int INITIAL_WINDOW_WIDTH  = 1280;

typedef std::function<void(double)>                                       GameLoopFunc;
typedef std::function<void(const class Renderer&)>                        GameDrawFunc;
typedef std::function<void(int key, int scancode, int action, int mode)> GameInputFunc;
typedef std::function<void(double x, double y)>                      GameCursorPosFunc;
typedef std::function<void(int button, int action, int mods)>       GameMouseInputFunc;
