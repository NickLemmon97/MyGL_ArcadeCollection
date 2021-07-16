#pragma once
#include <GamePCH.h>

class SpaceInvaders : public Game
{
public:
	SpaceInvaders();
	virtual ~SpaceInvaders();

	void DisplayRules();
	void Reset();

	void Init() override;
	void Update(float delta) override;
	void Draw(const class Renderer& renderer) override;

	void ShootBullet(float dir, glm::vec2 pos);

private:

	std::vector<class Projectile*> m_Projectiles;

};
