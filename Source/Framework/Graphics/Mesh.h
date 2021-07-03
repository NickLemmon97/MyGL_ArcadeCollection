#pragma once

//FrameworkImpl template class FrameworkAPI std::vector<GLfloat>;

typedef glm::vec2 VertexPosition;
typedef glm::vec3 VertexColor;


struct VertexFormat
{
	VertexPosition vertexPosition;
	VertexColor vertexColor;
};

class FrameworkAPI Mesh
{
	friend class Renderer;

public:
	Mesh();
	~Mesh();

	void Init(VertexFormat* vertices, GLuint count, GLenum primitive = GL_LINE_LOOP);

	void MakeTriangle();

	void Draw(const class Renderer& renderer);
	void Draw();

protected:

	GLenum PrimitiveType;

	GLuint m_Vbo;
	GLuint m_Vao;

	GLuint m_NumVerts;

private:

};
