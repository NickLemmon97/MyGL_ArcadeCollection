#pragma once

//FrameworkImpl template class FrameworkAPI std::vector<GLfloat>;

struct VertexFormat
{
	GLfloat xPos, yPos;
};

class FrameworkAPI Mesh
{
	friend class Renderer;

public:
	Mesh();
	~Mesh();

	void Init(VertexFormat* vertices, GLuint count, GLenum primitive = GL_LINE_LOOP);

	void MakeTriangle();

protected:

	GLenum PrimitiveType;

	GLuint m_Vbo;
	GLuint m_Vao;

	GLuint m_NumVerts;

private:

};
