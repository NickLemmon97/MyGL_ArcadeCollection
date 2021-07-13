#include "GamePCH.h"
#include "MyGameObject.h"
#include <Utilities/ColorList.h>

void MyGameObject::Init()
{
	m_Mesh->MakeSqaure(INITIAL_WINDOW_HEIGHT, ColorList::PURPLE);
	m_Position.x = INITIAL_WINDOW_WIDTH  * 0.5;
	m_Position.y = INITIAL_WINDOW_HEIGHT * 0.5;
}