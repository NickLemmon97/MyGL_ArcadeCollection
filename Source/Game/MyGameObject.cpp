#include "GamePCH.h"
#include "MyGameObject.h"
#include <Graphics/LineLoop.h>

void MyGameObject::Init()
{
	MyColor RED = { 1.0f,0.0f,0.0f };

	std::vector<glm::vec2> vertices =
	{
		{ 0.5f,  0.5f},
		{ 0.5f, -0.5f},
		{-0.5,  -0.5f},
		{-0.5f,  0.5f},
	};

	m_Mesh->Init(vertices, RED);

}

void MyGameObject::Update(double delta)
{

}
