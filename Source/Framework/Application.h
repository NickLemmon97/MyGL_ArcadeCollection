#pragma once

class App
{
	//Allow the AppInitializer to Initialize and run our application
	friend class AppInitializer;

	typedef std::function<void(double)>                                       GameLoopFunc;
	typedef std::function<void(const class Renderer&)>                        GameDrawFunc;
	typedef std::function<void(int key, int scancode, int action, int mode)> GameInputFunc;
	typedef std::function<void(double x, double y)>                      GameCursorPosFunc;

public:
	App();
	~App();

	struct GLFWwindow* GetGLFWWindow();

	void FrameworkAPI SetWindowTitle(const char* title);

	double FrameworkAPI GetGLFWTime();

	static FrameworkAPI App& GetAppInstance();

	int GetWindowHeight();
	int GetWindowWidth();
	void SetWindowHeight(int height);
	void SetWindowWidth(int width);

protected:

	bool Init();

	void Close();

	void Run();
	
	void Draw();

	static void HandleWindowResize(struct GLFWwindow* window, int width, int height);
	static void HandleInput(struct GLFWwindow* window, int key, int scancode, int action, int mode);
	static void HandleCursorPos(struct GLFWwindow* window, double x, double y);

	void SetGameLoop(GameLoopFunc loop);
	void SetGameDraw(GameDrawFunc draw);
	void SetGameInput(GameInputFunc input);
	void SetGameCursorFunc(GameCursorPosFunc cursor);

private:
	void SetGLWindowHints();
	void SetupGLFWCallbacks();

	struct GLFWwindow* m_pWindow = nullptr;

	class Renderer* m_pRenderer = nullptr;

	GameLoopFunc  GameLoop;
	GameDrawFunc  GameDraw;
	GameInputFunc GameInput;
	GameCursorPosFunc GameCursorFunc;

	int m_WindowHeight;
	int m_WindowWidth;

	double m_glfwTime;
};
