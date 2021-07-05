#include "GamePCH.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_Mesh = std::make_shared<Mesh>();
}

GameObject::~GameObject()
{
}

void GameObject::Draw(const Renderer& renderer)
{
	renderer.Draw(*m_Mesh.get());
}
