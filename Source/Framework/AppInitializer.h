#pragma once
#include <memory>
#include "../ProjectConfig.h"

FrameworkImpl template class FrameworkAPI std::shared_ptr<class App>;

class FrameworkAPI AppInitializer
{
public:
	AppInitializer(class IGameClass* game);

	void Run();

	bool Setup();

private:

	void SetupFunctionCallbacks();

	std::shared_ptr<class App> Application_;
	class IGameClass* Game_;
};