#pragma once
#include <memory>

class AppInitializer
{
public:
	AppInitializer(class Game* game);
	~AppInitializer();

	void Run();

	bool Setup();

private:

	void BindFunctionCallbacks();

	class App* Application_;
	class Game* Game_;
};