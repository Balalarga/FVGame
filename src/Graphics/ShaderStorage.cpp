#include "ShaderStorage.h"

#include "Utils/Files.h"
#include <iostream>

ShaderStorage::ShaderStorage()
{

}

ShaderStorage::~ShaderStorage()
{
    DestroyAll();
}

ShaderProgram *ShaderStorage::AddShaderProgram(const std::string &tag, const ShadersList &shaders, const std::vector<std::string> &uniforms)
{
    if(auto shaderProgram = GetShaderProgram(tag))
        return shaderProgram;

    ShaderProgram* program = new ShaderProgram();

    for(auto& [_, shader]: shaders)
        program->AddShader(shader);

    _shaderPrograms[tag] = program;

    return program;
}

ShaderProgram *ShaderStorage::AddShaderProgram(const std::string &tag, const ShadersList &shaders)
{
    return AddShaderProgram(tag, shaders, {});
}

Shader *ShaderStorage::AddShader(const std::string &tag, Shader::Type type, const std::string &path)
{
    if(auto shader = GetShader(tag))
        return shader;

    Shader* shader = new Shader(type, Files::ReadFile(path));

    _shaders[tag] = shader;

    return shader;
}

Shader *ShaderStorage::GetShader(const std::string &tag)
{
    auto mapIterator = _shaders.find(tag);
    if(mapIterator != _shaders.end())
        return (*mapIterator).second;
    return nullptr;
}

ShaderProgram *ShaderStorage::GetShaderProgram(const std::string &tag)
{
    auto mapIterator = _shaderPrograms.find(tag);
    if(mapIterator != _shaderPrograms.end())
        return (*mapIterator).second;
    return nullptr;
}

void ShaderStorage::CompileAll()
{
    for(auto& [tag, shader]: _shaders)
    {
        if(!shader->Compile())
            std::cout<<tag<<" compile error\n";
    }
    for(auto& [tag, shaderProgram]: _shaderPrograms)
    {
        if(!shaderProgram->Compile())
            std::cout<<tag<<" compile error\n";
    }
}

void ShaderStorage::DestroyAll()
{
    for(auto& [_, shaderProgram]: _shaderPrograms)
    {
        shaderProgram->Destroy();
    }
    for(auto& [_, shader]: _shaders)
    {
        shader->Destroy();
    }
}
