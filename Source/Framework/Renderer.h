#pragma once

#include "../ProjectConfig.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	FrameworkAPI void Draw(/*required params*/) const;
};