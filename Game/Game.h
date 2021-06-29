#pragma once

class Game
{
public:
	Game();
	~Game();

	void Update(double delta);
	void Draw();

private:

	double m_Count = 0.0;
	double previousSeconds = 0.0;
	int frameCount = 0;

};

