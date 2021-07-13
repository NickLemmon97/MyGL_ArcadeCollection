#include <FrameworkPCH.h>
#include <GamePCH.h>

#include "Game/DeathRace/DeathGame.h"
#include "Game/TrialGame/TrialGame.h"
#include "Game/Asteroids/AsteroidsGame.h"

#include <iostream>

using namespace std;

int AcknowledgeUserInput();

void ClearScreen();
void Pause();

void CheckMemLeaks();
void DumpMemLeaks();

template <class _Ty>
void PlayGame()
{
	AppInitializer app = { new _Ty() };
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
	CheckMemLeaks();

	cout << "Welcome to a collection of Arcade-style games!" << endl;

	while (int input = AcknowledgeUserInput())
	{
		ClearScreen();

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
		ClearScreen();
	}

	DumpMemLeaks();

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


void ClearScreen()
{
#if defined _WINDOWS
	system("cls");
#endif
}

void Pause()
{
#if defined DEBUG
#if defined _WINDOWS
	system("pause");
#else
	std::cin.get();
#endif
#endif
}



#if defined DEBUG && defined _WINDOWS && !defined TEMP_DONT_USE
#if CHECK_FOR_MEMORY_LEAKS
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif
#endif

void CheckMemLeaks()
{
#if defined DEBUG && defined _WINDOWS && !defined TEMP_DONT_USE
#if CHECK_FOR_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif
}

void DumpMemLeaks()
{
#if defined DEBUG && defined _WINDOWS && !defined TEMP_DONT_USE
#if CHECK_FOR_MEMORY_LEAKS
if (_CrtDumpMemoryLeaks())
{
	Logger::LogMessage(LogVerbosity::Error, "Memory Leaks were found!");
}
#endif
#endif
}
