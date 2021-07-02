#pragma once

FrameworkImpl template class FrameworkAPI std::function<void(double)>;
FrameworkImpl template class FrameworkAPI std::function<void(const class Renderer&)>;
FrameworkImpl template class FrameworkAPI std::function<void(int key, int scancode, int action, int mode)>;
FrameworkImpl template class FrameworkAPI std::function<void(double x, double y)>;

class FrameworkAPI App
{
	//Allow the AppInitializer to Initialize and run our application
	friend class AppInitializer;

	typedef std::function<void(double)>                                      GameLoopFunc;
	typedef std::function<void(const class Renderer&)>                       GameDrawFunc;
	typedef std::function<void(int key, int scancode, int action, int mode)> GameInputFunc;
	typedef std::function<void(double x, double y)>                      GameCursorPosFunc;

public:
	App();
	~App();

	struct GLFWwindow* GetGLFWWindow();

	void SetWindowTitle(const char* title);

	double GetGLFWTime();

	static App& GetAppInstance();

protected:

	bool Init();

	void Close();

	void Run();
	
	void Draw();

	static void HandleInput(struct GLFWwindow* window, int key, int scancode, int action, int mode);
	static void HandleCursorPos(struct GLFWwindow* window, double x, double y);

	void SetGameLoop(GameLoopFunc loop);
	void SetGameDraw(GameDrawFunc draw);
	void SetGameInput(GameInputFunc input);
	void SetGameCursorFunc(GameCursorPosFunc cursor);

private:

	void SetGLWindowHints();
	void SetupInputCallbacks();

	struct GLFWwindow* m_pWindow = nullptr;

	class Renderer* m_pRenderer = nullptr;

	GameLoopFunc  GameLoop;
	GameDrawFunc  GameDraw;
	GameInputFunc GameInput;
	GameCursorPosFunc GameCursorFunc;

	double m_glfwTime;
};
