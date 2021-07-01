#pragma once
#include <functional>

#include "../ProjectConfig.h"
#include "Debugging.h"

FrameworkImpl template class FrameworkAPI std::function<void(double)>;
FrameworkImpl template class FrameworkAPI std::function<void(const class Renderer&)>;
FrameworkImpl template class FrameworkAPI std::function<void(int key, int scancode, int action, int mode)>;

typedef FrameworkAPI std::function<void(double)>                                      GameLoopFunc;
typedef FrameworkAPI std::function<void(const class Renderer&)>                       GameDrawFunc;
typedef FrameworkAPI std::function<void(int key, int scancode, int action, int mode)> GameInputFunc;

class FrameworkAPI App
{
	template<typename _Ty>
	friend class AppInitializer;
	friend class AppInit2;

public:
	App();
	~App();

	void SetGameLoop(GameLoopFunc loop);
	void SetGameDraw(GameDrawFunc draw);
	void SetGameInput(GameInputFunc input);

	struct GLFWwindow* GetGLFWWindow();

	static App& GetAppInstance();

	void LogMessage(LogVerbosity verbosity, const char* message);

protected:

	bool Init();

	void Close();

	void Run();
	
	void Draw();

	static void HandleInput(struct GLFWwindow* window, int key, int scancode, int action, int mode);

private:
	struct GLFWwindow* m_pWindow = nullptr;

	class Renderer* m_pRenderer = nullptr;

	GameLoopFunc  GameLoop;
	GameDrawFunc  GameDraw;
	GameInputFunc GameInput;
};
