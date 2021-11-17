#ifndef SHADERSTORAGE_H
#define SHADERSTORAGE_H

#include "ShaderProgram.h"
#include <memory>

using wShaderProgram = std::weak_ptr<ShaderProgram>;

class ShaderStorage
{
public:
    ShaderStorage();
    virtual ~ShaderStorage();

    ShaderProgram* AddShaderProgram(const std::string& tag, const ShadersList& shaders,
                       const std::vector<std::string>& uniforms);
    ShaderProgram* AddShaderProgram(const std::string& tag, const ShadersList& shaders);

    Shader* AddShader(const std::string& tag, Shader::Type type, const std::string& path);

    Shader* GetShader(const std::string& tag);
    ShaderProgram* GetShaderProgram(const std::string& tag);

    void CompileAll();
    void DestroyAll();

private:
    std::map<std::string, Shader*> _shaders;
    std::map<std::string, ShaderProgram*> _shaderPrograms;
};

#endif // SHADERSTORAGE_H
