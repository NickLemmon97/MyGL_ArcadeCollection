#pragma once

class Renderer
{
public:
	Renderer()  = default;
	~Renderer() = default;

	void Init();
	void FrameworkAPI UseShader(std::string&& shaderName);

	void FrameworkAPI BeginDraw() const;

	void FrameworkAPI Draw(const class Shape&, const glm::vec2& pos, float rotation) const;
	void FrameworkAPI DrawUI(const class Shape&, const glm::vec2& pos, glm::vec2& anchor, float rotation) const;

	void FrameworkAPI SetBackgroundColor(glm::vec3 color);

	void SetProjection(float w, float h);
	void SetCameraPosition(float x, float y);

private:
	std::unique_ptr<ShaderProgram> m_ShapeShader;
	std::unique_ptr<ShaderProgram> m_UIShapeShader;
};