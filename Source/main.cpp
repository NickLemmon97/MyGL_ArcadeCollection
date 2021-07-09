//#include <AppInitializer.h>
//#include <Core/Game.h>
#include <FrameworkPCH.h>
#include <GamePCH.h>

#include <iostream>

using namespace std;

int AcknowledgeUserInput();

int main(int argc, char** argv)
{
#if defined DEBUG && defined _WINDOWS && !defined TEMP_DONT_USE
#if CHECK_FOR_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
	{
#endif
#endif

		cout << "Welcome to a collection of games!" << endl;

		while (int input = AcknowledgeUserInput() != 0)
		{
			system("cls");

			switch (input)
			{
			case 0:
				break;
			default:
				std::shared_ptr<Game> theGame = std::make_shared<Game>();
				AppInitializer theApp = { theGame.get() };
			}

			system("cls");
		}


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

int AcknowledgeUserInput()
{
	int num;

	cout << "Please select a game by inputing the number:\n"
		<< "1. Default\n"
		<< "0. Exit"
		<< endl;

	cin >> num;
	while (true)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> num;
		}

		if (!cin.fail()) break;
	}

	return num;
}
