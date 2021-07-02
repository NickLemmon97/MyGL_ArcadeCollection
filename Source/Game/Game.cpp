#include <GamePCH.h>

DECLARE_LOG_CATEGORY(LogGame);

Game::Game()
{
	frameCount = 0;

	LOG_MESSAGE(LogGame, LogVerbosity::Success, "Game Created!");
}

Game::~Game()
{
}

void Game::Init()
{
	m_Triangle = std::make_shared<Mesh>();
	m_Triangle->MakeTriangle();

	m_Mess = std::make_shared<Mesh>();
	VertexFormat verts[] = {
	VertexFormat{  0.8f,  0.0f},
	VertexFormat{  0.4f,  0.6f},
	VertexFormat{  0.1f,  0.8f},
	VertexFormat{ -0.3f,  0.4f},
	VertexFormat{ -0.7f,  0.1f},
	VertexFormat{ -0.3f, -0.6f}
	};

	m_Mess->Init(verts, 6, GL_LINE_LOOP);
}

void Game::Update(double delta)
{
	ShowFPS(delta);
}

void Game::Draw(const Renderer& renderer)
{
	renderer.BeginDraw();

	DrawMyShape
		? renderer.Draw(*m_Triangle.get())
		: renderer.Draw(*m_Mess.get());

	renderer.EndDraw();
}

void Game::HandleInput(int key, int scancode, int action, int mode)
{
	//DEBUG_LOG_MESSAGE(LogGame, LogVerbosity::Warning, "Input is being handled");

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
