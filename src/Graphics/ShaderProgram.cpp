#include "ShaderProgram.h"

#include <GL/glew.h>
#include <iostream>

ShaderProgram::ShaderProgram():
    _shaderProgramName(""),
    _handler(0),
    _isCreated(false)
{

}

ShaderProgram::~ShaderProgram()
{
    Destroy();
}

void ShaderProgram::Bind()
{
    glUseProgram(_handler);
}

void ShaderProgram::Release()
{
    glUseProgram(0);
}

void ShaderProgram::SetName(const std::string &shaderName)
{
    _shaderProgramName = shaderName;
}

void ShaderProgram::SetLayout(const ShadersLayout &layout)
{
    _layout = layout;
}

void ShaderProgram::AddShader(Shader *shader)
{
    _shaders[shader->GetType()] = shader;
}

void ShaderProgram::AddUniform(const std::string &name)
{
    _uniforms[name] = -1;
}

void ShaderProgram::AddUniforms(const std::vector<std::string> &names)
{
    for(auto& name: names)
        _uniforms[name] = -1;
}

bool ShaderProgram::Compile()
{
    _handler = glCreateProgram();

    for(auto& [type, shader]: _shaders)
    {
        if(shader->IsCreated() || shader->Compile())
            glAttachShader(_handler, shader->GetId());
    }

    glLinkProgram(_handler);

    _isCreated = CheckProgram();
    if(!_isCreated)
        Destroy();

    for(auto& [name, location]: _uniforms)
    {
        location = glGetUniformLocation(_handler, name.c_str());
        if(location < 0)
            std::cout<<"[Warning] "<<_shaderProgramName<<" lost "<<name<<" uniform location\n";
    }

    return _isCreated;
}

void ShaderProgram::Destroy()
{
    glDeleteProgram(_handler);

    _handler = 0;
    _isCreated = false;
}

bool ShaderProgram::IsCreated()
{
    return _isCreated;
}

void ShaderProgram::SetUniform(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(_uniforms[name], 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::mat3 &mat)
{
    glUniformMatrix3fv(_uniforms[name], 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::mat2 &mat)
{
    glUniformMatrix2fv(_uniforms[name], 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::vec4 &vec)
{
    glUniform4fv(_uniforms[name], 1, &vec[0]);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::vec3 &vec)
{
    glUniform3fv(_uniforms[name], 1, &vec[0]);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::vec2 &vec)
{
    glUniform2fv(_uniforms[name], 1, &vec[0]);
}

void ShaderProgram::SetUniform(const std::string &name, const float &val)
{
    glUniform1f(_uniforms[name], val);
}

void ShaderProgram::SetUniform(const std::string &name, const int &val)
{
    glUniform1i(_uniforms[name], val);
}

void ShaderProgram::SetUniform(const std::string &name, const unsigned &val)
{
    glUniform1ui(_uniforms[name], val);
}

void ShaderProgram::SetUniform(const std::string &name, const bool &val)
{
    glUniform1i(_uniforms[name], val);
}

bool ShaderProgram::CheckProgram()
{
    GLint isLinked = 0;
    glGetProgramiv(_handler, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_handler, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(_handler, maxLength, &maxLength, &errorLog[0]);
        for(auto i: errorLog)
            std::cout<<i;
        std::cout<<std::endl;

        return false;
    }
    return true;
}
