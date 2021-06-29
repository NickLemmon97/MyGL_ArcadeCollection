#pragma once

class IGameClass
{
public:

	virtual void Update(double delta) = 0;
	virtual void Draw() = 0;

	virtual void Clean()
	{

	}

};

