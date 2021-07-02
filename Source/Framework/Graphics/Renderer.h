#pragma once

class FrameworkAPI Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();

	void BeginDraw() const;
	void EndDraw() const;

	void DrawTriangle(/*required params*/) const;
	void Draw(const class Mesh&) const;

	std::unique_ptr<ShaderProgram> m_Shader;
};