#pragma once
#include <GameClass.h>

GameImpl template class GameAPI std::shared_ptr<class Mesh>;
//GameImpl template class GameAPI std::vector<glm::vec2>;

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
	std::shared_ptr<class Mesh> m_Mess;

	void ShowFPS(double delta);

	double fpsTime = 0.0;
	int frameCount = 0;

	glm::vec2 m_Position;

	bool DrawMyShape = true;
};
