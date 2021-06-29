#include <iostream>
#include <AppInitializer.h>
#include <Game.h>


int main(int argc, char** argv)
{
#ifdef DEBUG
	#if CHECK_FOR_MEMORY_LEAKS
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
		{
	#endif
#endif


	AppInitializer<FPSDraw> FPS;
	AppInitializer<CoutGame> Cout;


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

