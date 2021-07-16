#pragma once
#include <memory>
#include "../ProjectConfig.h"

class FrameworkAPI AppInitializer
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