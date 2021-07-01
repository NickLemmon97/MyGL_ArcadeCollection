#include <FrameworkPCH.h>

static App* _sInstance;

App::App()
{
	_sInstance = this;

	m_pRenderer = new Renderer();
}

App::~App()
{
	_sInstance = nullptr;

	if (m_pRenderer != nullptr)
	{
		delete m_pRenderer;
	}
	m_pRenderer = nullptr;

}

bool App::Init()
{
	if (!glfwInit())
	{
		std::cerr << RED_CONSOLE_TEXT << "Failed to initialize glfw" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	m_pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_TITLE, nullptr, nullptr);

	if (m_pWindow == nullptr)
	{
		std::cerr << RED_CONSOLE_TEXT << "Failed to create a GLFW window" << std::endl;

		glfwTerminate();

		return false;
	}

	glfwMakeContextCurrent(m_pWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << RED_CONSOLE_TEXT << "Failed to initialize glew" << std::endl;

		glfwTerminate();

		return false;
	}

	glfwSetKeyCallback(m_pWindow, HandleInput);

	return true;
}

void App::Close()
{
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

	//Initialize the clear color just once here
	glClearColor(0.23f, 0.56f, 0.89f, 1.0f);

	double previousTime = 0.0;

	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwPollEvents();

		double currentTime = glfwGetTime();
		double deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		GameLoop(deltaTime);

		Draw();
	} 
}

void App::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	GameDraw(*m_pRenderer);

	glfwSwapBuffers(m_pWindow);
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

GLFWwindow* App::GetGLFWWindow()
{
	return m_pWindow;
}

App& App::GetAppInstance()
{
	return *_sInstance;
}

void App::LogMessage(LogVerbosity verbosity, const char* message)
{
	switch (verbosity)
	{
	case LogVerbosity::Log:
		std::cout << WHITE_CONSOLE_TEXT;
		break;

	case LogVerbosity::Warning:
		std::cout << YELLOW_CONSOLE_TEXT;
		break;

	case LogVerbosity::Error:
		std::cout << RED_CONSOLE_TEXT;
		break;
	}

	std::cout << message << WHITE_CONSOLE_TEXT << std::endl;
}

