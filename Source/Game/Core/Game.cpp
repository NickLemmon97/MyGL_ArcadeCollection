#include <GamePCH.h>
#include "Trial/Ship.h"
#include "Button.h"

#include "DeathRace/Car.h"
//#include "DeathRace/Person.h"


//int CarIdx;
//int ShipIdx;

Game::Game()
{
	frameCount = 0;

	m_GameObjects.push_back(std::make_shared<MyGameObject>());
	m_GameObjects.push_back(std::make_shared<Ship>(this));
	m_GameObjects.push_back(std::make_shared<ExitButton>(this));
	m_GameObjects.push_back(std::make_shared<Car>(this));
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
	App::Get().GetRenderer().SetBackgroundColor(ColorList::DARKGRAY);

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


	if (m_GameObjects[1]->IsOverlappingWithOther(m_GameObjects[2]->GetPosition(), m_GameObjects[2]->GetScale()))
	{
		m_GameObjects[1]->HandleBeginOverlap();
	}
	else
	{
		m_GameObjects[1]->HandleEndOverlap();
	}

	if (m_GameObjects[3]->IsOverlappingWithOther(m_GameObjects[1]->GetPosition(), m_GameObjects[1]->GetScale()))
	{
		m_GameObjects[3]->HandleBeginOverlap();
	}
	else
	{
		m_GameObjects[3]->HandleEndOverlap();
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
