#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init() = 0;
	virtual void Update(double delta) = 0;
	virtual void Draw(const class Renderer& renderer);

protected:
	std::shared_ptr<class Mesh> m_Mesh;

};

