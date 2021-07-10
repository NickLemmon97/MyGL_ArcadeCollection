#include <FrameworkPCH.h>

AppInitializer::AppInitializer(IGameClass* game)
{
	Game_ = game;
	Run();
}

AppInitializer::~AppInitializer()
{
	Game_ = nullptr;
}

void AppInitializer::Run()
{
	Application_ = std::make_shared<App>();
	if (Setup())
	{
		Game_->Init();
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

	SetupFunctionCallbacks();

	return true;
}

void AppInitializer::SetupFunctionCallbacks()
{
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

	GameCursorPosFunc cursor = std::bind(&IGameClass::HandleMousePosition, Game_, std::placeholders::_1, std::placeholders::_2);
	Application_->SetGameCursorFunc(cursor);

	GameMouseInputFunc mouse = std::bind(&IGameClass::HandleMouseInput, Game_, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	Application_->SetGameMouseInputFunc(mouse);
}
