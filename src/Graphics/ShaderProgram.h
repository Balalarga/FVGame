#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <map>

#include "Shader.h"
#include "ShadersLayout.h"

using ShadersList = std::map<Shader::Type, Shader*>;

class Scene;

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void Bind();
    void Release();

    void SetName(const std::string& shaderName);
    void SetLayout(const ShadersLayout& layout);

    void AddShader(Shader *shader);
    void AddUniform(const std::string& name);

    void SetUniforms(Scene* scene);

    bool Compile();
    void Destroy();

    bool IsCreated();

    inline const ShadersLayout& GetLayout(){ return _layout; }


protected:
    bool CheckProgram();


private:
    unsigned _handler;
    bool _isCreated;

    std::string _shaderProgramName;

    ShadersList _shaders;
    std::map<std::string, unsigned> _uniforms;
    ShadersLayout _layout;
};

#endif // SHADERPROGRAM_H
