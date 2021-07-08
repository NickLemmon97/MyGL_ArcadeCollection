#include <GamePCH.h>
#include <string>
#include <LuaGameConfig.h>

using namespace Utils;
using namespace std;

Game::Game()
{
	frameCount = 0;

	LuaGameConfig lgc(this);
}

Game::~Game()
{
}

void Game::Exit()
{
	App::Get().RequestExit();
}

void Game::Init()
{
	int count = 0;
	for (auto& go : m_GameObjects)
	{
		go->Init();
		count++;
	}

	cout << "Initialized " << count << " Game objects" << endl;

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Game Initialized!");	
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
	renderer.BeginDraw();

	for (auto& go : m_GameObjects)
	{
		go->Draw(renderer);
	}
}

void Game::HandleInput(int key, int scancode, int action, int mode)
{
	switch (key)
	{
	case GLFW_KEY_SPACE:
		if (action == GLFW_PRESS)
		{

		}
		break;
	}

	for (auto& func : m_InputFunctions)
	{
		func(key, scancode, action, mode);
	}
}

void Game::HandleMousePosition(double x, double y)
{
	for (auto& func : m_CursorPosFuncs)
	{
		func(x, y);
	}
}

void Game::HandleMouseInput(int button, int action, int mods)
{
	for (auto& func : m_MouseInputFuncs)
	{
		func(button, action, mods);
	}
}

void Game::RegisterForInputCallback(GameCursorPosFunc func)
{
	m_CursorPosFuncs.push_back(func);
}

void Game::RegisterForInputCallback(GameMouseInputFunc func)
{
	m_MouseInputFuncs.push_back(func);
}

GameObject* Game::AddGameObject()
{
	m_GameObjects.push_back(std::make_shared<GameObject>());

	DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Log, "Gameobject added to game");

	return m_GameObjects.at(m_GameObjects.size() - 1).get();
}

void Game::RegisterForInputCallback(GameInputFunc func)
{
	m_InputFunctions.push_back(func);
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
		App::Get().SetWindowTitle(ostream.str().c_str());

		fpsTime = 0.0f;
		frameCount = 0;
	}
	frameCount++;
}
