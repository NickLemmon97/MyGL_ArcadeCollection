#pragma once
#include <memory>
#include "../ProjectConfig.h"

FrameworkImpl template class FrameworkAPI std::shared_ptr<class App>;

class FrameworkAPI AppInitializer
{
public:
	AppInitializer(class IGameClass* game);
	~AppInitializer();

	void Run();

	bool Setup();

private:

	void BindFunctionCallbacks();

	std::shared_ptr<class App> Application_;
	class IGameClass* Game_;
};