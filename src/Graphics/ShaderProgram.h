#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <map>
#include <glm/glm.hpp>

#include "Shader.h"
#include "ShadersLayout.h"

class Scene;



using ShadersList = std::map<Shader::Type, Shader*>;

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
    void AddUniforms(const std::vector<std::string>& names);

    bool Compile();
    void Destroy();

    bool IsCreated();

    inline const ShadersLayout& GetLayout(){ return _layout; }

    void SetUniform(const std::string& name, const glm::mat4& mat);
    void SetUniform(const std::string& name, const glm::mat3& mat);
    void SetUniform(const std::string& name, const glm::mat2& mat);
    void SetUniform(const std::string& name, const glm::vec4& vec);
    void SetUniform(const std::string& name, const glm::vec3& vec);
    void SetUniform(const std::string& name, const glm::vec2& vec);
    void SetUniform(const std::string& name, const float& val);
    void SetUniform(const std::string& name, const int& val);
    void SetUniform(const std::string& name, const unsigned& val);
    void SetUniform(const std::string& name, const bool& val);


protected:
    bool CheckProgram();


private:
    unsigned _handler;
    bool _isCreated;

    std::string _shaderProgramName;

    ShadersList _shaders;
    std::map<std::string, int> _uniforms;
    ShadersLayout _layout;
};

#endif // SHADERPROGRAM_H
