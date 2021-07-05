#include "GamePCH.h"
#include "MyGameObject.h"

void MyGameObject::Init()
{
	m_Mesh->SetPrimitiveType(GL_TRIANGLE_FAN);

	VertexColor RED = { 1.0f,0.0f,0.0f };

	VertexFormat vertices[] =
	{
		{{  0.5f,  0.5f}, RED},
		{{  0.5f, -0.5f}, RED},
		{{ -0.5,  -0.5f}, RED},
		{{ -0.5f,  0.5f}, RED},
	};

	m_Mesh->Init(vertices, 4);

}

void MyGameObject::Update(double delta)
{

}
