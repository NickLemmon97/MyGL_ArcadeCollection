#pragma once

class IGameClass
{
public:

	virtual void Update(double delta) = 0;
	virtual void Draw(const class Renderer& renderer) = 0;

	virtual void Clean()
	{

	}

};

