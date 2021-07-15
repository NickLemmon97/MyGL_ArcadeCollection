#pragma once
#include <GamePCH.h>

class Brick : public GameObject
{
public:
	Brick(class Ball* ball, int idx);

	void Init() override;
	void Update(double delta) override;

private:
	class Ball* m_pBall = nullptr;

	glm::vec3 m_Col;

	glm::vec3 Colors[6] =
	{
		ColorList::BLUE,
		ColorList::GREEN,
		ColorList::RED,
		ColorList::PURPLE,
		ColorList::WHITE,
		ColorList::CYAN,
	};

};