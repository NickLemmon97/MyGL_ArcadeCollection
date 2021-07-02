#include <FrameworkPCH.h>
#include <GamePCH.h>

int main(int argc, char** argv)
{
#if defined DEBUG || defined DEVELOPMENT
#if CHECK_FOR_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
	{
#endif
#endif


		std::shared_ptr<Game> g2 = std::make_shared<Game>();
		AppInitializer Game = { g2.get() };


#if defined DEBUG || defined DEVELOPMENT
#if CHECK_FOR_MEMORY_LEAKS
	}
	if (_CrtDumpMemoryLeaks())
	{
		std::cerr << RED_CONSOLE_TEXT << "Memory leaks found were found" << WHITE_CONSOLE_TEXT << std::endl;
	}
#endif
#endif

#if defined DEVELOPMENT && defined _WINDOWS
	system("pause"); //Checking logs during a non visual studio executed development build
#endif

	return 0;
}

