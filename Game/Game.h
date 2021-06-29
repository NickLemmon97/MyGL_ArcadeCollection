#pragma once
#include <GameClass.h>

class Game : public IGameClass
{
public:
	Game();
	~Game();

	void Update(double delta) override;
	void Draw() override;

private:
	double m_Count = 0.0;

	double previousSeconds = 0.0;
	int frameCount = 0;
};

class CoutGame : public IGameClass 
{
public:
	void Update(double delta) override;

	void Draw() override
	{

	}

private:
	double m_Count = 0.0;
};

class FPSDraw : public IGameClass
{
public:
	void Update(double delta) override
	{

	}

	void Draw() override;

private:

	double previousSeconds = 0.0;
	int frameCount = 0;

};
