#include <FrameworkPCH.h>
#include <GamePCH.h>

#include "Game/DeathRace/DeathGame.h"
#include "Game/TrialGame/TrialGame.h"
#include "Game/Asteroids/AsteroidsGame.h"

#include <iostream>

#if defined DEBUG && defined _WINDOWS && !defined TEMP_DONT_USE
#if CHECK_FOR_MEMORY_LEAKS
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif
#endif

using namespace std;

int AcknowledgeUserInput();

template <class _Ty>
void PlayGame()
{
	std::shared_ptr<_Ty> game = std::make_shared<_Ty>();
	AppInitializer app = { game.get() };
}

void OutputSelection()
{
	cout << "Please select a game by inputing the number:\n"
		<< "1. Death Race\n"
		<< "2. Asteroids\n"
		<< "0. Exit"
		<< endl;
}


int main(int argc, char** argv)
{
#if defined DEBUG && defined _WINDOWS && !defined TEMP_DONT_USE
#if CHECK_FOR_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
#endif
#endif

		cout << "Welcome to a collection of games!" << endl;

		while (int input = AcknowledgeUserInput())
		{
#if defined _WINDOWS
			system("cls");
#endif

			switch (input)
			{
			case 1:
				cout << "Playing Death Race\n";
				PlayGame<DeathRace>();
				break;
			case 2:
				cout << "Playing Asteroids\n";
				PlayGame<AsteroidsGame>();
				break;
			default:
				cout << "Not a valid game\n";
				break;
			}

#if defined _WINDOWS
			system("cls");
#endif
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

	OutputSelection();

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
