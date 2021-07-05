#pragma once

class FrameworkAPI LineLoop
{
public:
	LineLoop();
	~LineLoop();

	void Init(std::vector<glm::vec2>& points, MyColor& col);

	void Draw(ShaderProgram* shader);

protected:
	MyColor m_LineCol;

	GLuint m_Vbo;
	GLuint m_Vao;

	GLuint m_NumVerts;
};

