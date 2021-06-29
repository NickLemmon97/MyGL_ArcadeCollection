#pragma once
#include <iostream>
#include <memory>
#include <type_traits>
#include <Application.h>
#include <GameClass.h>


template<typename GameType>
class AppInitializer
{
public:
	AppInitializer();
	void Run();
	bool Setup();

	std::shared_ptr<App> GetApplication()
	{
		return Application_;
	}

	std::shared_ptr<GameType> GetGame()
	{
		return Game_;
	}

private:

	std::shared_ptr<App> Application_;
	std::shared_ptr<GameType> Game_;

};


template<typename GameType>
inline AppInitializer<GameType>::AppInitializer()
{
#ifdef DEBUG
	if (std::is_base_of<IGameClass, GameType>::value){
#endif 

		Run();

#ifdef DEBUG
	}else{
		std::cerr << RED_CONSOLE_TEXT << "Wasn't a Game, make sure your class inherits from IGameClass" << WHITE_CONSOLE_TEXT << std::endl;
	}
#endif
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

	Game_ = std::make_shared<GameType>();

	App::GameLoopFunc loop = std::bind(&IGameClass::Update, Game_, std::placeholders::_1);
	Application_->SetGameLoop(loop);

	App::GameDrawFunc draw = std::bind(&IGameClass::Draw, Game_, std::placeholders::_1);
	Application_->SetGameDraw(draw);

	return true;
}