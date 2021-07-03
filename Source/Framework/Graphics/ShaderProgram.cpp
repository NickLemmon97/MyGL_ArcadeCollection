#include <FrameworkPCH.h>
#include "ShaderProgram.h"

DECLARE_LOG_CATEGORY(LogShader);

ShaderProgram::ShaderProgram()
    :m_VertexShader    { 0 }
    , m_FragmentShader { 0 }
    , m_Program        { 0 }
{
}

ShaderProgram::ShaderProgram(const char* shader)
    : m_VertexShader{ 0 }
    , m_FragmentShader{ 0 }
    , m_Program{ 0 }
{
    LoadShader(shader);
}

ShaderProgram::ShaderProgram(const char* vertex, const char* fragment)
    : m_VertexShader{ 0 }
    , m_FragmentShader{ 0 }
    , m_Program{0 }
{
    LoadShader(vertex, fragment);
}

ShaderProgram::~ShaderProgram()
{
    Cleanup();
}

bool ShaderProgram::LoadShader(const char* filename)
{
    std::string vertex{ filename };
    vertex.append(".vert");

    std::string fragment{ filename };
    fragment.append(".frag");

    return LoadShader(vertex.c_str(), fragment.c_str());
}

bool ShaderProgram::LoadShader(const char* vertex, const char* fragment)
{
    m_VertexShaderCode = Utilities::LoadCompleteFileFromData(vertex);
    if (m_VertexShaderCode == nullptr)
    {
        DEBUG_LOG_MESSAGE(LogShader, LogVerbosity::Error, "Failed to load Vertex Shader");
        return false;
    }

    m_FragmentShaderCode = Utilities::LoadCompleteFileFromData(fragment);
    if (m_FragmentShaderCode == nullptr)
    {
        DEBUG_LOG_MESSAGE(LogShader, LogVerbosity::Error, "Failed to load Fragment Shader");
        return false;
    }

    return ReloadShaderProgram();
}

bool ShaderProgram::ReloadShaderProgram()
{
    assert(m_VertexShaderCode != nullptr);
    assert(m_FragmentShaderCode != nullptr);

    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    CompileShader(m_VertexShader, m_VertexShaderCode);
    CompileShader(m_FragmentShader, m_FragmentShaderCode);

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
    if (m_VertexShaderCode != nullptr)
        delete[] m_VertexShaderCode;
    m_VertexShaderCode = nullptr;

    if (m_FragmentShaderCode != nullptr)
        delete[] m_FragmentShaderCode;
    m_FragmentShaderCode = nullptr;

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

void ShaderProgram::SetUniform(const GLchar* name, const glm::vec2& value)
{
    GLint loc = GetUniformLocation(name);
    glUniform2f(loc, value.x, value.y);
}

void ShaderProgram::SetUniform(const GLchar* name, const glm::vec3& value)
{
    GLint loc = GetUniformLocation(name);
    glUniform3f(loc, value.x, value.y, value.z);
}

void ShaderProgram::SetUniform(const GLchar* name, const glm::vec4& value)
{
    GLint loc = GetUniformLocation(name);
    glUniform4f(loc, value.x, value.y, value.z, value.w);
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
