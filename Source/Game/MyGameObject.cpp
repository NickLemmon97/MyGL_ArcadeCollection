#include "GamePCH.h"
#include "MyGameObject.h"
#include <Utilities/ColorList.h>

void MyGameObject::Init()
{
	m_Mesh->MakeSqaure(INITIAL_WINDOW_HEIGHT/2, ColorList::PURPLE);
	m_Position.x = INITIAL_WINDOW_WIDTH  * 0.5;
	m_Position.y = INITIAL_WINDOW_HEIGHT * 0.5;
}

void MyGameObject::Update(double delta)
{
}
