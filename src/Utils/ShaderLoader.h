#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <string>

#include "rapidjson/document.h"

class ShaderLoader
{
public:
    ShaderLoader() = delete;

    static void LoadShadersFrom(const std::string& pathToJson);

private:
    static void LoadShaders(const rapidjson::Value &root);
    static void LoadShaderProgram(const rapidjson::Value &root);
};

#endif // SHADERLOADER_H
