#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(double delta);
	virtual void Draw(const Renderer& renderer);

protected:
	std::shared_ptr<class Shape> m_Mesh;
};
