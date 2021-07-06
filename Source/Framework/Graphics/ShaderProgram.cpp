#include <FrameworkPCH.h>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
    :m_VertexShader    { 0 }
    , m_FragmentShader { 0 }
    , m_Program        { 0 }
{
}

ShaderProgram::ShaderProgram(std::string shader)
    : m_Program{ 0 }
{
    LoadShader(shader);
}

ShaderProgram::ShaderProgram(std::string vertex, std::string fragment)
    : m_Program{ 0 }
{
    LoadShader(vertex, fragment);
}

ShaderProgram::~ShaderProgram()
{
    Cleanup();
}

bool ShaderProgram::LoadShader(std::string filename)
{
    std::string vertex{ filename };
    vertex.append(".vert");

    std::string fragment{ filename };
    fragment.append(".frag");

    return LoadShader(vertex, fragment);
}

bool ShaderProgram::LoadShader(std::string&& vert, std::string&& frag)
{
    return LoadShader(vert, frag);
}

bool ShaderProgram::LoadShader(std::string& vertex, std::string& fragment)
{
    m_VertexShaderCode = Utilities::LoadShaderFromData(vertex);

    m_FragmentShaderCode = Utilities::LoadShaderFromData(fragment);

    return ReloadShaderProgram();
}

bool ShaderProgram::ReloadShaderProgram()
{

    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    CompileShader(m_VertexShader, m_VertexShaderCode.c_str());
    CompileShader(m_FragmentShader, m_FragmentShaderCode.c_str());

    if (m_VertexShader == 0 || m_FragmentShader == 0)
    {
        Cleanup();
        return false;
    }

    m_Program = glCreateProgram();
    glAttachShader(m_Program, m_VertexShader);
    glAttachShader(m_Program, m_FragmentShader);

    glLinkProgram(m_Program);

    int linked = 0;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &linked);
    if (linked == 0)
    {
        int infolen = 0;
        glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &infolen);

        char* infobuffer = new char[infolen + 1];
        glGetProgramInfoLog(m_Program, infolen + 1, nullptr, infobuffer);
        DEBUG_LOG_MESSAGE(LogShader, LogVerbosity::Error, infobuffer);
        assert(false);
        delete[] infobuffer;

        Cleanup();
        return false;
    }

    return true;
}

void ShaderProgram::CompileShader(GLuint& shaderHandle, const char* shaderString)
{
    const char* strings[] = { shaderString };
    glShaderSource(shaderHandle, 1, strings, nullptr);

    glCompileShader(shaderHandle);

    int compiled = 0;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
    if (compiled == 0)
    {
        int infolen = 0;
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &infolen);

        char* infobuffer = new char[infolen + 1];
        glGetShaderInfoLog(shaderHandle, infolen + 1, nullptr, infobuffer);
        DEBUG_LOG_MESSAGE(LogShader, LogVerbosity::Error, infobuffer);
        assert(false);
        delete[] infobuffer;

        glDeleteShader(shaderHandle);
        shaderHandle = 0;
    }
}

void ShaderProgram::Cleanup()
{
    glDetachShader(m_Program, m_VertexShader);
    glDetachShader(m_Program, m_FragmentShader);

    if (m_VertexShader)
        glDeleteShader(m_VertexShader);
    if (m_FragmentShader)
        glDeleteShader(m_FragmentShader);
    if (m_Program)
        glDeleteProgram(m_Program);

    m_VertexShader = 0;
    m_FragmentShader = 0;
    m_Program = 0;
}

GLuint ShaderProgram::GetProgram()
{
    return m_Program;
}

void ShaderProgram::Use()
{
    if(m_Program > 0)
        glUseProgram(m_Program);
}

void ShaderProgram::SetUniform(const GLchar* name, const glm::vec2& v)
{
    GLint loc = GetUniformLocation(name);
    glUniform2f(loc, v.x, v.y);
}

void ShaderProgram::SetUniform(const GLchar* name, const glm::vec3& v)
{
    GLint loc = GetUniformLocation(name);
    glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::SetUniform(const GLchar* name, const glm::vec4& v)
{
    GLint loc = GetUniformLocation(name);
    glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void ShaderProgram::SetUniform(const GLchar* name, const glm::mat4& m)
{
    GLint loc = GetUniformLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

GLint ShaderProgram::GetUniformLocation(const GLchar* name)
{
    std::map<std::string, GLint>::iterator it = m_UniformLocations.find(name);

    if (it == m_UniformLocations.end())
    {
        m_UniformLocations[name] = glGetUniformLocation(m_Program, name);
    }

    return m_UniformLocations[name];
}
