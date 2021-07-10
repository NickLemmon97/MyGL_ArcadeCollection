#pragma once

#include <map>

class ShaderProgram
{
public:
	FrameworkAPI ShaderProgram();
	FrameworkAPI ShaderProgram(std::string shader);
	FrameworkAPI ShaderProgram(std::string vertex, std::string fragment);
	FrameworkAPI ~ShaderProgram();

	bool FrameworkAPI LoadShader(std::string filename);
	bool FrameworkAPI LoadShader(std::string&& vert, std::string&& frag);
	bool FrameworkAPI LoadShader(std::string& vertex, std::string& fragment);

	bool ReloadShaderProgram();

	void CompileShader(GLuint& shader, const char* shaderstring);

	void Cleanup();

	GLuint GetProgram();

	void FrameworkAPI Use();

	void SetUniform(const GLchar* name, const float f);
	void SetUniform(const GLchar* name, const glm::vec2& v);
	void SetUniform(const GLchar* name, const glm::vec3& v);
	void SetUniform(const GLchar* name, const glm::vec4& v);
	void SetUniform(const GLchar* name, const glm::mat4& m);

protected:

	GLint GetUniformLocation(const GLchar* name);

	std::string m_FragmentShaderCode;
	std::string m_VertexShaderCode;

	GLuint m_VertexShader, m_FragmentShader, m_Program;

	std::map<std::string, GLint> m_UniformLocations;

private:
};

