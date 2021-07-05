#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(double delta);
	virtual void Draw(ShaderProgram* shader);

protected:
	std::shared_ptr<class LineLoop> m_Mesh;
};

