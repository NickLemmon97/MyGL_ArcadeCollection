#include <FrameworkPCH.h>
#include <GamePCH.h>

#define TEMP_DONT_USE

int main(int argc, char** argv)
{
#if defined DEBUG && defined _WINDOWS && !defined TEMP_DONT_USE
#if CHECK_FOR_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
	{
#endif
#endif


		std::shared_ptr<Game> theGame = std::make_shared<Game>();
		AppInitializer theApp = { theGame.get() };


#if defined DEBUG && defined _WINDOWS && !defined TEMP_DONT_USE
#if CHECK_FOR_MEMORY_LEAKS
	}
	if (_CrtDumpMemoryLeaks())
	{
#if defined _WINDOWS
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		std::cerr << "Memory leaks found were found" << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
#else
		std::cerr << RED_CONSOLE_TEXT << "Memory leaks found were found" << WHITE_CONSOLE_TEXT << std::endl;
#endif
	}
#endif
#endif

#if defined DEBUG && defined _WINDOWS
	system("pause");
#endif

	return 0;
}

