#include "GamePCH.h"
#include "Meteor.h"

#ifdef _WINDOWS
#include "mmsystem.h"
#endif

using namespace std;

Meteor::Meteor()
{
	Reset();
}

void Meteor::Init()
{
	std::vector<glm::vec2> vertices;

	int count = Random::RandomInt(8, 18);

	float divisions = 6.28f / count;

	for (int i = 0; i < count; i++)
	{
		float radius = Random::RandomFloat(13.0f, 39.0f);
		m_Scale.x += radius;
		m_Scale.y += radius;
		vertices.push_back({ cosf(i * divisions) * radius, sinf(i * divisions) * radius });
	}

	m_Scale.x /= count;
	m_Scale.y /= count;

	GameObject::Init();

	m_Mesh->Init(vertices, ColorList::WHITE, GL_LINE_LOOP);
}

void Meteor::Update(float delta)
{
	m_Rotation += m_RotationDirection * delta;

	if (m_Velocity.y > 150.0f) m_Velocity.y = 150.0f;
	if (m_Velocity.x > 150.0f) m_Velocity.x = 150.0f;

	m_Position.x += m_Velocity.x * delta;
	m_Position.y += m_Velocity.y * delta;

	ScreenWrapPosition();
}

void Meteor::Reset()
{
	m_Position.x = Random::RandomFloat(INITIAL_WINDOW_WIDTH * 0.5f + 200, INITIAL_WINDOW_WIDTH + 300);
	m_Position.y = Random::RandomFloat(INITIAL_WINDOW_HEIGHT * 0.5f + 100, INITIAL_WINDOW_HEIGHT + 300);

	if (m_Position.x > INITIAL_WINDOW_WIDTH) m_Position.x -= INITIAL_WINDOW_WIDTH;
	if (m_Position.y > INITIAL_WINDOW_HEIGHT) m_Position.y -= INITIAL_WINDOW_HEIGHT;

	m_RotationDirection = Random::RandomFloat(-3, 3);

	float speed = Random::RandomFloat(40.0f, 120.0f);
	float dir = Random::RandomFloat(0.0f, 6.28f);

	m_Velocity.x = cosf(dir) * speed;
	m_Velocity.y = sinf(dir) * speed;

	bIsActive = true;
}

void Meteor::HandleBeginOverlap()
{
	GameObject::HandleBeginOverlap();
	bIsActive = false;

#ifdef _WINDOWS
	PlaySound(TEXT("Data/Audio/Destroy.wav"), NULL, SND_FILENAME | SND_ASYNC);
#endif
}
