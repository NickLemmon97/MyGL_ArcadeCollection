#pragma once
#include <GameClass.h>

class Game : public IGameClass
{
public:
	GameAPI Game();
	GameAPI ~Game();

	void Exit();

	void Init() override;
	void Update(double delta) override;
	void Draw(const class Renderer& renderer) override;
	void HandleInput(int key, int scancode, int action, int mode) override;
	void HandleMousePosition(double x, double y) override;
	void HandleMouseInput(int button, int action, int mods) override;

	void RegisterForInputCallback(GameInputFunc func);
	void RegisterForInputCallback(GameCursorPosFunc func);
	void RegisterForInputCallback(GameMouseInputFunc func);

protected:
	std::vector<std::shared_ptr<class GameObject>> m_GameObjects;

	std::vector<GameInputFunc> m_InputFunctions;
	std::vector<GameCursorPosFunc> m_CursorPosFuncs;
	std::vector<GameMouseInputFunc> m_MouseInputFuncs;

//Stats
private:
	void ShowFPS(double delta);

	double fpsTime = 0.0;
	int frameCount = 0;

};
