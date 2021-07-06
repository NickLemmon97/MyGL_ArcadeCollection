#include "GamePCH.h"
#include "MyGameObject.h"
#include <Utilities/ColorList.h>

void MyGameObject::Init()
{
	std::vector<glm::vec2> vertices =
	{
		{ 0.5f,  0.5f},
		{ 0.5f, -0.5f},
		{-0.5,  -0.5f},
		{-0.5f,  0.5f},
	};

	m_Mesh->Init(vertices, ColorList::RED);
}

void MyGameObject::Update(double delta)
{
}
