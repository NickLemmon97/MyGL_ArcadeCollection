#include "AppInitializer.h"

#include <Application.h>
#include <GameClass.h>

AppInitializer::AppInitializer(IGameClass* game)
{
	Game_ = game;
	Run();
}

void AppInitializer::Run()
{
	Application_ = std::make_shared<App>();
	if (Setup())
	{
		Application_->Run();
	}
	Application_->Close();
}

bool AppInitializer::Setup()
{
	if (!Application_->Init())
	{
		std::cerr << RED_CONSOLE_TEXT << "Application was unable to initialize, will be closing" << std::endl;
		return false;
	}

	App::GameLoopFunc loop = std::bind(&IGameClass::Update, Game_, std::placeholders::_1);
	Application_->SetGameLoop(loop);

	App::GameDrawFunc draw = std::bind(&IGameClass::Draw, Game_, std::placeholders::_1);
	Application_->SetGameDraw(draw);

	App::GameInputFunc input = std::bind(&IGameClass::HandleInput, Game_,
		std::placeholders::_1,
		std::placeholders::_2,
		std::placeholders::_3,
		std::placeholders::_4);
	Application_->SetGameInput(input);

	return true;
}
