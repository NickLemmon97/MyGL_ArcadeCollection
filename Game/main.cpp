#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Application.h>
#include <Constants.h>
#include <Debugging.h>

#include "Game.h"


int main(int argc, char** argv)
{

#ifdef DEBUG
#if CHECK_FOR_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
	{
#endif
#endif


	std::shared_ptr<App> Application = std::make_shared<App>();
	std::shared_ptr<Game> Game_ = std::make_shared<Game>();

	if (!Application->Init())
	{
		std::cerr << RED_CONSOLE_TEXT << "Application was unable to initialize, will be closing" << std::endl;
		return -1;
	}

	App::GameLoopFunc loop = std::bind(&Game::Update, Game_, std::placeholders::_1);
	Application->SetGameLoop(loop);

	App::GameDrawFunc draw = std::bind(&Game::Draw, Game_);
	Application->SetGameDraw(draw);


	Application->Run();

	Application->Close();


#ifdef DEBUG
#if CHECK_FOR_MEMORY_LEAKS
	}
	_CrtDumpMemoryLeaks();
#endif
#endif

	return 0;
}

