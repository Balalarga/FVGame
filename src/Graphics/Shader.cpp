#include "Shader.h"

#include <GL/glew.h>
#include <iostream>
#include <vector>

unsigned GetOpenGLType(Shader::Type type)
{
    switch(type)
    {
    case Shader::Type::Vertex:
        return GL_VERTEX_SHADER;
    case Shader::Type::Fragment:
        return GL_FRAGMENT_SHADER;
    case Shader::Type::Geometry:
        return GL_GEOMETRY_SHADER;
    default:
        return 0;
    }
}

Shader::Shader(Type type, const std::string &source):
    _isCreated(false),
    _type(type),
    _handler(0),
    _sourceCode(source)
{
}

Shader::Shader():
    Shader(Type::None, "")
{
}

Shader::~Shader()
{
    Destroy();
}

bool Shader::Compile()
{
    if(_type == Type::None)
        return false;

    _handler = glCreateShader(GetOpenGLType(_type));
    const char* rawSource = _sourceCode.c_str();

    glShaderSource(_handler, 1, &rawSource, 0);
    glCompileShader(_handler);

    _isCreated = CheckErrors();
    if(!_isCreated)
        Destroy();

    return _isCreated;
}

void Shader::Destroy()
{
    if(_handler)
        glDeleteShader(_handler);

    _handler = 0;
    _isCreated = false;
}

bool Shader::IsCreated()
{
    return _isCreated;
}

Shader::Type Shader::GetType() const
{
    return _type;
}

unsigned Shader::GetId() const
{
    return _handler;
}

bool Shader::CheckErrors()
{
    GLint isCompiled = 0;
    glGetShaderiv(_handler, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(_handler, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(_handler, maxLength, &maxLength, &errorLog[0]);
        for(auto i: errorLog)
        {
            std::cout<<i;
        }
        std::cout<<std::endl;

        return false;
    }
    return true;
}
