#pragma once

//Constants
static const char* APP_TITLE = "Arcade Collection";

constexpr int INITIAL_WINDOW_HEIGHT = 720;
constexpr int INITIAL_WINDOW_WIDTH  = 1280;
constexpr int HALF_WINDOW_HEIGHT    = INITIAL_WINDOW_HEIGHT * 0.5f;
constexpr int HALF_WINDOW_WIDTH     = INITIAL_WINDOW_WIDTH  * 0.5f;

typedef std::function<void(double)>                                       GameLoopFunc;
typedef std::function<void(const class Renderer&)>                        GameDrawFunc;
typedef std::function<void(int key, int scancode, int action, int mode)> GameInputFunc;
typedef std::function<void(double x, double y)>                      GameCursorPosFunc;
typedef std::function<void(int button, int action, int mods)>       GameMouseInputFunc;
