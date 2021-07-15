#pragma once
#include <memory>
#include "../ProjectConfig.h"

class FrameworkAPI AppInitializer
{
public:
	AppInitializer(class IGameClass* game);
	~AppInitializer();

	void Run();

	bool Setup();

private:

	void BindFunctionCallbacks();

	class App* Application_;
	class IGameClass* Game_;
};