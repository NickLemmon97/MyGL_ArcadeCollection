#pragma once
#include <GameClass.h>

class Game : public IGameClass
{
public:
	Game();
	~Game();

	void Update(double delta) override;
	void Draw(const class Renderer& renderer) override;
	void HandleInput(int key, int scancode, int action, int mode) override;

private:

	void ShowFPS();

	double m_Count = 0.0;

	double previousSeconds = 0.0;
	int frameCount = 0;
};
