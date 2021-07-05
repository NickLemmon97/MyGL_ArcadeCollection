#include "GamePCH.h"
#include "GameObject.h"
#include <Graphics/LineLoop.h>

GameObject::GameObject()
{
	m_Mesh = std::make_shared<LineLoop>();
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::Update(double delta)
{
}

void GameObject::Draw(ShaderProgram* shader)
{
	m_Mesh->Draw(shader);
}
