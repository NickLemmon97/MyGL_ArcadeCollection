#include <GamePCH.h>


Game::Game()
{
	m_Count = 0.0;
	previousSeconds = 0.0;
	frameCount = 0;
}

Game::~Game()
{
}

void Game::Init()
{
	m_Triangle = std::make_shared<Mesh>();
	m_Triangle->MakeTriangle();

	m_Mess = std::make_shared<Mesh>();
	std::vector<GLfloat> verts = {
		 0.8f, 0.0f,
		 0.4f, 0.6f,
		 0.1f, 0.8f,
		-0.3f, 0.4f,
		-0.7f, 0.1f,
		-0.3f, -0.6f
	};
	m_Mess->SetVertices(verts);

}

void Game::Update(double delta)
{
	m_Count += delta;

	if (m_Count > 2.0)
	{
		App::GetAppInstance().LogMessage(LogVerbosity::Warning, "Update is looping after 2 seconds");
		m_Count = 0.0;
	}

	ShowFPS();
}

void Game::Draw(const Renderer& renderer)
{
	DrawMyShape
		? renderer.Draw(*m_Triangle.get())
		: renderer.Draw(*m_Mess.get());
}

void Game::HandleInput(int key, int scancode, int action, int mode)
{
	App::GetAppInstance().LogMessage(LogVerbosity::Warning, "Input is being handled");

	switch (key)
	{
	case GLFW_KEY_SPACE:
		if(action == GLFW_PRESS)
			DrawMyShape = !DrawMyShape;
		break;
	}

}

void Game::HandleMousePosition(double x, double y)
{
	char xx[255];
	_itoa_s(x, xx, 10);
	App::GetAppInstance().LogMessage(LogVerbosity::Log, xx);
	_itoa_s(y, xx, 10);
	App::GetAppInstance().LogMessage(LogVerbosity::Log, xx);
}

void Game::ShowFPS()
{
	double currentSeconds = App::GetAppInstance().GetGLFWTime();

	double elapsedSeconds = currentSeconds - previousSeconds;

	if (elapsedSeconds > 0.5)
	{
		previousSeconds = currentSeconds;
		double fps = double(frameCount) / elapsedSeconds;
		double msPerFrame = 1000 / fps;

		std::ostringstream ostream;
		ostream.precision(3);
		ostream << std::fixed << APP_TITLE << "  " << "FPS: " << fps << "  " << "Frame Time: " << msPerFrame << "ms";
		App::GetAppInstance().SetWindowTitle(ostream.str().c_str());

		frameCount = 0;
	}

	frameCount++;
}
