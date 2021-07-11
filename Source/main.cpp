#include <FrameworkPCH.h>
#include <GamePCH.h>

#include "Game/DeathRace/DeathGame.h"
#include "Game/TrialGame/TrialGame.h"

#include <iostream>

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
		<< "1. Default\n"
		<< "2. Death Race\n"
		<< "3. Trial Game\n"
		<< "0. Exit"
		<< endl;
}

int main(int argc, char** argv)
{
#if defined DEBUG && defined _WINDOWS && !defined TEMP_DONT_USE
#if CHECK_FOR_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
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
			case 0:
				//Should not reach here.  Explicitly Defining 0
				break;
			case 1:
				cout << "Playing Game 1\n";
				PlayGame<Game>();
				break;
			case 2:
				cout << "Playing Game 2\n";
				PlayGame<DeathRace>();
				break;
			case 3:
				cout << "Playing Game 3\n";
				PlayGame<TrialGame>();
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
