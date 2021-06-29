#pragma once
#include <iostream>
#include <memory>
#include <Application.h>
#include <GameClass.h>


template<typename GameType>
class AppInitializer
{
public:
	AppInitializer();
	void Run();
	bool Setup();

private:

	std::shared_ptr<App> Application_;
	std::shared_ptr<IGameClass> Game_;

};


template<typename GameType>
inline AppInitializer<GameType>::AppInitializer()
{
	Run();
}


template<typename GameType>
inline void AppInitializer<GameType>::Run()
{
	Application_ = std::make_shared<App>();
	if (Setup())
	{
		Application_->Run();
	}
	Application_->Close();
}

template<typename GameType>
inline bool AppInitializer<GameType>::Setup()
{
	if (!Application_->Init())
	{
		std::cerr << RED_CONSOLE_TEXT << "Application was unable to initialize, will be closing" << std::endl;
		return false;
	}

	//if GameType is not equal to a IGameClass then notify the user and return false

	Game_ = std::make_shared<GameType>();

	App::GameLoopFunc loop = std::bind(&IGameClass::Update, Game_, std::placeholders::_1);
	Application_->SetGameLoop(loop);

	App::GameDrawFunc draw = std::bind(&IGameClass::Draw, Game_);
	Application_->SetGameDraw(draw);

	return true;
}