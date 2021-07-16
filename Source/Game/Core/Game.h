#pragma once

class GameAPI Game
{
public:
	Game();
	virtual ~Game();

	void Exit();
	void DisplayRules();
	virtual void Reset();

	virtual void Init();
	virtual void Update(double delta);
	virtual void Draw(const class Renderer& renderer);
	void HandleInput(int key, int scancode, int action, int mode);
	void HandleMousePosition(double x, double y);
	void HandleMouseInput(int button, int action, int mods);

	void RegisterForInputCallback(GameInputFunc func);
	void RegisterForInputCallback(GameCursorPosFunc func);
	void RegisterForInputCallback(GameMouseInputFunc func);

protected:
	std::vector<class GameObject*> m_GameObjects;
	std::vector<class UIObject*> m_UIElements;

	class Shape* m_GameBoundary;

	std::vector<GameInputFunc> m_InputFunctions;
	std::vector<GameCursorPosFunc> m_CursorPosFuncs;
	std::vector<GameMouseInputFunc> m_MouseInputFuncs;
};
