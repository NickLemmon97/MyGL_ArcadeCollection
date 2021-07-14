#pragma once
#include <GamePCH.h>

class Brick : public GameObject
{
public:
	Brick();

	void Init() override;
	void Update(double delta) override;
};