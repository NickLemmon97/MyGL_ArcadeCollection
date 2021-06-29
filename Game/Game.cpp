#include "Game.h"

#include <Application.h>
#include <Constants.h>
#include <GLFW/glfw3.h>

#include <sstream>


Game::Game()
{
}

Game::~Game()
{
}

void Game::Update(double delta)
{
	m_Count += delta;

	if (m_Count > 2.0)
	{
		App::GetAppInstance().LogMessage(LogVerbosity::Warning, "Update is looping after 2 seconds");
		m_Count = 0.0;
	}

}

void Game::Draw()
{
	double elapsedSeconds;
	double currentSeconds = glfwGetTime();

	elapsedSeconds = currentSeconds - previousSeconds;

	if (elapsedSeconds > 0.5)
	{
		previousSeconds = currentSeconds;
		double fps = double(frameCount) / elapsedSeconds;
		double msPerFrame = 1000 / fps;

		std::ostringstream ostream;
		ostream.precision(3);
		ostream << std::fixed << APP_TITLE << "  " << "FPS: " << fps << "  " << "Frame Time: " << msPerFrame << "ms";
		glfwSetWindowTitle(App::GetAppInstance().GetGLFWWindow(), ostream.str().c_str());

		frameCount = 0;
	}

	frameCount++;
}


void CoutGame::Update(double delta)
{
	m_Count += delta;

	if (m_Count > 2.0)
	{
		App::GetAppInstance().LogMessage(LogVerbosity::Warning, "Update is looping after 2 seconds");
		m_Count = 0.0;
	}
}


void FPSDraw::Draw()
{
	double elapsedSeconds;
	double currentSeconds = glfwGetTime();

	elapsedSeconds = currentSeconds - previousSeconds;

	if (elapsedSeconds > 0.5)
	{
		previousSeconds = currentSeconds;
		double fps = double(frameCount) / elapsedSeconds;
		double msPerFrame = 1000 / fps;

		std::ostringstream ostream;
		ostream.precision(3);
		ostream << std::fixed << APP_TITLE << "  " << "FPS: " << fps << "  " << "Frame Time: " << msPerFrame << "ms";
		glfwSetWindowTitle(App::GetAppInstance().GetGLFWWindow(), ostream.str().c_str());

		frameCount = 0;
	}

	frameCount++;
}
