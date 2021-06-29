#pragma once
#include <functional>

#include "Debugging.h"

int main(int argc, char** argv);

class App
{
	//Allow the main function to access the Run method
	friend int ::main(int argc, char** argv);

	typedef std::function<void(double)> GameLoopFunc;
	typedef std::function<void()> GameDrawFunc;

public:
	App();
	~App();

	void SetGameLoop(GameLoopFunc loop);
	void SetGameDraw(GameDrawFunc draw);

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

	GameLoopFunc GameLoop;
	GameDrawFunc GameDraw;
};