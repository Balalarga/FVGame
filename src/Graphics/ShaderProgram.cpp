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
