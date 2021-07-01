#include <iostream>
#include <memory>
#include <AppInitializer.h>
#include <Game.h>
#include "ProjectConfig.h"

int main(int argc, char** argv)
{
#ifdef DEBUG
#if CHECK_FOR_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
	{
#endif
#endif

		Game* g = new Game();
		//AppInitializer<Game> FPS;
		AppInit2 Game = { g };

		delete g;

#ifdef DEBUG
#if CHECK_FOR_MEMORY_LEAKS
	}
	if (_CrtDumpMemoryLeaks())
	{
		std::cerr << RED_CONSOLE_TEXT << "Memory leaks found were found" << WHITE_CONSOLE_TEXT << std::endl;
	}
#endif
#endif

	return 0;
}

