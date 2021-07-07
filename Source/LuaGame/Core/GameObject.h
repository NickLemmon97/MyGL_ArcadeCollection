#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(double delta);
	virtual void Draw(const Renderer& renderer);

	virtual void LoadLuaScript(const char* name);

protected:
	std::shared_ptr<class Shape> m_Mesh;

	lua_State* L;

	glm::vec2 m_Position;
};
