#pragma once
#include <iostream>
#include <memory>
#include <type_traits>
#include <Application.h>
#include <GameClass.h>

FrameworkImpl template class FrameworkAPI std::shared_ptr<App>;

template<typename GameType>
class FrameworkAPI AppInitializer
{
public:
	AppInitializer()
	{
	#ifdef DEBUG 
		if (std::is_base_of<IGameClass, GameType>::value) { 
	#endif 

		Run();

	#ifdef DEBUG
	} else { std::cerr << RED_CONSOLE_TEXT << "Wasn't a Game, make sure your class inherits from IGameClass" << WHITE_CONSOLE_TEXT << std::endl; }
	#endif
	}

	void Run()
	{
		Application_ = std::make_shared<App>();
		if (Setup())
		{
			Application_->Run();
		}
		Application_->Close();
	}

	bool Setup()
	{
		if (!Application_->Init())
		{
			std::cerr << RED_CONSOLE_TEXT << "Application was unable to initialize, will be closing" << std::endl;
			return false;
		}

		Game_ = std::make_shared<GameType>();

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

class FrameworkAPI AppInit2
{
public:
	AppInit2(IGameClass* game);

	void Run();

	bool Setup();

private:

	std::shared_ptr<App> Application_;
	IGameClass* Game_;
};