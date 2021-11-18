#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <string>


class ShaderLoader
{
public:
    ShaderLoader() = delete;

    static void ReadShaders(const std::string& pathToJson);
};

#endif // SHADERLOADER_H
