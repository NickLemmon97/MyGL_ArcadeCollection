#pragma once
#include <GamePCH.h>

class Pedestrian : public GameObject
{
public:
	void Init() override;
	void Update(double delta) override;
	void Draw(const class Renderer& renderer) override;

	bool GetIsDead();

	void HandleBeginOverlap() override;

private:

	bool bIsDead;

};