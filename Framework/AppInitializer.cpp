#include "AppInitializer.h"

AppInit2::AppInit2(IGameClass* game)
{
	Game_ = game;
	Run();
}

void AppInit2::Run()
{
	Application_ = std::make_shared<App>();
	if (Setup())
	{
		Application_->Run();
	}
	Application_->Close();
}

bool AppInit2::Setup()
{
	if (!Application_->Init())
	{
		std::cerr << RED_CONSOLE_TEXT << "Application was unable to initialize, will be closing" << std::endl;
		return false;
	}

	GameLoopFunc loop = std::bind(&IGameClass::Update, Game_, std::placeholders::_1);
	Application_->SetGameLoop(loop);

	GameDrawFunc draw = std::bind(&IGameClass::Draw, Game_, std::placeholders::_1);
	Application_->SetGameDraw(draw);

	GameInputFunc input = std::bind(&IGameClass::HandleInput, Game_,
		std::placeholders::_1,
		std::placeholders::_2,
		std::placeholders::_3,
		std::placeholders::_4);
	Application_->SetGameInput(input);

	return true;
}
