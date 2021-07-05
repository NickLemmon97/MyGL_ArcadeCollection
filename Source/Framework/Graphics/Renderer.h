#pragma once

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();
	void FrameworkAPI UseShader(std::string&& shaderName);

	void FrameworkAPI BeginDraw() const;
	void FrameworkAPI EndDraw() const;
		 
	void FrameworkAPI Draw(const class Mesh&) const;

private:
	std::unique_ptr<ShaderProgram> m_Shader;
};