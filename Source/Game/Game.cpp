#include <GamePCH.h>

DECLARE_LOG_CATEGORY(LogGame);

Game::Game()
{
	frameCount = 0;

	m_GameObjects.push_back(std::make_shared<MyGameObject>());
}

Game::~Game()
{
}

void Game::Init()
{
	for (auto& go : m_GameObjects)
	{
		go->Init();
	}

	m_Shader = std::make_shared<ShaderProgram>("simple");

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Game Created!");	
}

void Game::Update(double delta)
{
	ShowFPS(delta);

	for (auto& go : m_GameObjects)
	{
		go->Update(delta);
	}
}

void Game::Draw(const Renderer& renderer)
{
	//renderer.BeginDraw();
	
	m_Shader->Use();

	for (auto& go : m_GameObjects)
	{
		go->Draw(m_Shader.get());
	}

	//renderer.EndDraw();
}

void Game::HandleInput(int key, int scancode, int action, int mode)
{
	//DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Warning, "Input is being handled");

	switch (key)
	{
	case GLFW_KEY_SPACE:
		if (action == GLFW_PRESS)
		{

		}
		break;
	}
}

void Game::HandleMousePosition(double x, double y)
{
	//char xx[255];
	//_itoa_s(int(x), xx, 10);
	//DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Log, xx);
	//_itoa_s(int(y), xx, 10);
	//DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Log, xx);
}

void Game::ShowFPS(double delta)
{
	fpsTime += delta;
	if (fpsTime > 1)
	{
		double fps = double(frameCount) / fpsTime;
		double msPerFrame = 1000 / fps;

		std::ostringstream ostream;
		ostream.precision(3);
		ostream << std::fixed << APP_TITLE << "  " << "FPS: " << fps << "  " << "Frame Time: " << msPerFrame << "ms";
		App::GetAppInstance().SetWindowTitle(ostream.str().c_str());

		fpsTime = 0.0f;
		frameCount = 0;
	}

	frameCount++;
}
