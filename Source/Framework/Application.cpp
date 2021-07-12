#include <FrameworkPCH.h>
#include <Application.h>

static App* _sInstance;

#ifdef DEBUG
void ShowFPS(double delta);
#endif

App::App()
{
	_sInstance = this;

	m_glfwTime = 0.0;

	m_WindowHeight = INITIAL_WINDOW_HEIGHT;
	m_WindowWidth = INITIAL_WINDOW_WIDTH;
}

App::~App()
{
	Close();
}

bool App::Init()
{
	if (!glfwInit())
	{
		DEBUG_LOG_MESSAGE(LogApplication, LogVerbosity::Error, "Failed to initialize glfw");
		return false;
	}

	SetGLWindowHints();

	m_pWindow = glfwCreateWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, APP_TITLE, nullptr, nullptr);

	if (m_pWindow == nullptr)
	{
		DEBUG_LOG_MESSAGE(LogApplication, LogVerbosity::Error, "Failed to create a GLFW window");
		glfwTerminate();

		return false;
	}

	glfwMakeContextCurrent(m_pWindow);

	glewExperimental = GL_FALSE;
	if (glewInit() != GLEW_OK)
	{
		DEBUG_LOG_MESSAGE(LogApplication, LogVerbosity::Error, "Failed to initialize glew");
		glfwTerminate();

		return false;
	}

	m_pRenderer = new Renderer();
	m_pRenderer->Init();
	m_pRenderer->SetProjection(
		float(INITIAL_WINDOW_WIDTH) ,
		float(INITIAL_WINDOW_HEIGHT));

	SetupGLFWCallbacks();

	LOG_MESSAGE(LogApplication, LogVerbosity::Success, "Application was Initialized");

	return true;
}

void App::Close()
{
	_sInstance = nullptr;

	if (m_pRenderer != nullptr)
	{
		delete m_pRenderer;
	}
	m_pRenderer = nullptr;

	glfwTerminate();
}

void App::Run()
{
	if (!GameLoop)
	{
		std::cerr << RED_CONSOLE_TEXT << "Game loop function was not set and application will close" << std::endl;
		return;
	}
	if (!GameDraw)
	{
		std::cerr << RED_CONSOLE_TEXT << "Game Draw function was not set and application will close" << std::endl;
		return;
	}

	double previousTime = 0.0;

	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwPollEvents();

		m_glfwTime = glfwGetTime();
		double deltaTime = m_glfwTime - previousTime;
		previousTime = m_glfwTime;

		GameLoop(deltaTime);

#ifdef DEBUG
		ShowFPS(deltaTime);
#endif

		Draw();
	} 
}

void App::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	GameDraw(*m_pRenderer);

	glfwSwapBuffers(m_pWindow);
}

void App::HandleWindowResize(GLFWwindow* window, int width, int height)
{
	_sInstance->SetWindowWidth( width );
	_sInstance->SetWindowHeight(height);
	glViewport(0, 0, width, height);

	_sInstance->m_pRenderer->SetProjection(1.0f/float(width)/2.0f, 1.0f/float(height)/2.0f);
}

void App::HandleInput(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	default:
		//do nothing;
		break;
	}

	_sInstance->GameInput(key, scancode, action, mode);
}

void App::HandleCursorPos(GLFWwindow* window, double x, double y)
{
	_sInstance->GameCursorFunc(x, _sInstance->GetWindowHeight() - y);
}

void App::HandleMouseInput(GLFWwindow* window, int button, int action, int mods)
{
	_sInstance->GameMouseInput(button, action, mods);
}

void App::SetGameLoop(GameLoopFunc loop)
{
	GameLoop = loop;
}

void App::SetGameDraw(GameDrawFunc draw)
{
	GameDraw = draw;
}

void App::SetGameInput(GameInputFunc input)
{
	GameInput = input;
}

void App::SetGameCursorFunc(GameCursorPosFunc cursor)
{
	GameCursorFunc = cursor;
}

void App::SetGameMouseInputFunc(GameMouseInputFunc mouse)
{
	GameMouseInput = mouse;
}

void App::SetGLWindowHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void App::SetupGLFWCallbacks()
{
	glfwSetKeyCallback(m_pWindow, HandleInput);
	glfwSetCursorPosCallback(m_pWindow, HandleCursorPos);
	glfwSetMouseButtonCallback(m_pWindow, HandleMouseInput);

	glfwSetFramebufferSizeCallback(m_pWindow, HandleWindowResize);
}

GLFWwindow* App::GetGLFWWindow()
{
	return m_pWindow;
}

void App::SetWindowTitle(const char* title)
{
	glfwSetWindowTitle(m_pWindow, title);
}

double App::GetGLFWTime()
{
	return m_glfwTime;
}

App& App::Get()
{
	return *_sInstance;
}

int App::GetWindowHeight()
{
	return m_WindowHeight;
}

int App::GetWindowWidth()
{
	return m_WindowWidth;
}

void App::SetWindowHeight(int height)
{
	m_WindowHeight = height;
}

void App::SetWindowWidth(int width)
{
	m_WindowWidth = width;
}

void App::RequestExit()
{
	glfwSetWindowShouldClose(m_pWindow, GL_TRUE);
}

Renderer& App::GetRenderer()
{
	return *m_pRenderer;
}

#ifdef DEBUG
float fpsTime = 0.0f;
int frameCount = 0;

#include <sstream>

void ShowFPS(double delta)
{
	fpsTime += delta;
	if (fpsTime > 1)
	{
		double fps = double(frameCount) / fpsTime;
		double msPerFrame = 1000 / fps;

		std::ostringstream ostream;
		ostream.precision(3);
		ostream << std::fixed << "Debug Game" << "  " << "FPS: " << fps << "  " << "Frame Time: " << msPerFrame << "ms";
		App::Get().SetWindowTitle(ostream.str().c_str());

		fpsTime = 0.0f;
		frameCount = 0;
	}
	frameCount++;
}
#endif

