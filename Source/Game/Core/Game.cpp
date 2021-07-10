#include <GamePCH.h>
#include "Button.h"

Game::Game()
{
	frameCount = 0;

	m_GameObjects.push_back(std::make_shared<ExitButton>(this));
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
	for (auto& go : m_GameObjects)
	{
		go->Init();
	}
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
	DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Log, "Registered a Cursor Position Callback Funciton");
	m_CursorPosFuncs.push_back(func);
}

void Game::RegisterForInputCallback(GameMouseInputFunc func)
{
	DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Log, "Registered a Mouse Input Callback Funciton");
	m_MouseInputFuncs.push_back(func);
}

void Game::RegisterForInputCallback(GameInputFunc func)
{
	DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Log, "Registered a Keyboard Input Callback Funciton");
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

