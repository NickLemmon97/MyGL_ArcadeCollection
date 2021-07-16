#pragma once

//Constants
static const char* APP_TITLE = "Arcade Collection";


constexpr int INITIAL_WINDOW_HEIGHT =  720;
constexpr int INITIAL_WINDOW_WIDTH  = 1280;
constexpr float HALF_WINDOW_HEIGHT  =  360;
constexpr float HALF_WINDOW_WIDTH   =  640;


typedef std::function<void(float delta)>                                  GameLoopFunc;
typedef std::function<void(double x, double y)>                      GameCursorPosFunc;
typedef std::function<void(const class Renderer&)>                        GameDrawFunc;
typedef std::function<void(int button, int action, int mods)>       GameMouseInputFunc;
typedef std::function<void(int key, int scancode, int action, int mode)> GameInputFunc;
