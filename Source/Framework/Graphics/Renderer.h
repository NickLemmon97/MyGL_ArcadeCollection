#pragma once

class Renderer
{
public:
	Renderer()  = default;
	~Renderer() = default;

	void Init();
	void FrameworkAPI UseShader(std::string&& shaderName);

	void FrameworkAPI BeginDraw() const;
		 
	void FrameworkAPI Draw(const class Mesh&) const;

	void FrameworkAPI Draw(const class Shape&) const;
	void FrameworkAPI Draw(const class Shape&, const glm::vec2& pos) const;

	void FrameworkAPI SetBackgroundColor(glm::vec3 color);

	void SetProjection(float w, float h);

private:
	std::unique_ptr<ShaderProgram> m_ShapeShader;
};