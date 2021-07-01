#pragma once
#include <GameClass.h>


class GameAPI Game : public IGameClass
{
public:
	Game();
	~Game();

	void Init() override;
	void Update(double delta) override;
	void Draw(const class Renderer& renderer) override;
	void HandleInput(int key, int scancode, int action, int mode) override;
	void HandleMousePosition(double x, double y) override;

private:

	std::shared_ptr<class Mesh> m_Triangle;

	void ShowFPS();

	double m_Count = 0.0;

	double previousSeconds = 0.0;
	int frameCount = 0;

	bool DrawMyShape = true;
};
