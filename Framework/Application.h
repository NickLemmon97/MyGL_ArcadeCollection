#pragma once
#include <functional>

#include "Debugging.h"

class App
{
	template<typename _Ty>
	friend class AppInitializer;

	typedef std::function<void(double)> GameLoopFunc;
	typedef std::function<void(const class Renderer&)> GameDrawFunc;
	typedef std::function<void(int key, int scancode, int action, int mode)> GameInputFunc;

public:
	App();
	~App();

	void SetGameLoop(GameLoopFunc loop);
	void SetGameDraw(GameDrawFunc draw);
	void SetGameInput(GameInputFunc input);

	struct GLFWwindow* GetGLFWWindow() const;

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