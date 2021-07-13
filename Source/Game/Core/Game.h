#pragma once
#include <GameClass.h>

class GameAPI Game : public IGameClass
{
public:
	Game();
	virtual ~Game();

	void Exit();
	void DisplayRules();
	void Reset();

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
	std::vector<std::shared_ptr<class UIElement>> m_UIElements;

	std::shared_ptr<class Shape> m_GameBoundary;

	std::vector<GameInputFunc> m_InputFunctions;
	std::vector<GameCursorPosFunc> m_CursorPosFuncs;
	std::vector<GameMouseInputFunc> m_MouseInputFuncs;

};
