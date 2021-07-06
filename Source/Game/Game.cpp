#include <GamePCH.h>
#include "Trial/Ship.h"

Game::Game()
{
	frameCount = 0;

	m_GameObjects.push_back(std::make_shared<MyGameObject>());
	m_GameObjects.push_back(std::make_shared<Ship>(this));
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

void Game::RegisterForInputCallback(GameCursorPosFunc func)
{
	m_CursorPosFuncs.push_back(func);
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
		App::GetAppInstance().SetWindowTitle(ostream.str().c_str());

		fpsTime = 0.0f;
		frameCount = 0;
	}
	frameCount++;
}
