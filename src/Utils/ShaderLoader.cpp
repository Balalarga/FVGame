#include "ShaderLoader.h"

#include <assert.h>
#include <iostream>

#include "MainWindow.h"
#include "Files.h"

using namespace rapidjson;

void ShaderLoader::LoadShadersFrom(const std::string &pathToJson)
{
    assert(MainWindow::IsCreated());

    Document document;
    document.Parse(Files::ReadFile(pathToJson).c_str());
    assert(document.IsObject());
    Value doc = document.GetObject();
    assert(doc.HasMember("Shaders"));
    assert(doc.HasMember("ShaderPrograms"));

    Value shaders = doc["Shaders"].GetArray();
    Value shaderPrograms = doc["ShaderPrograms"].GetArray();

    if(shaders.IsArray())
        LoadShaders(shaders);

    if(shaderPrograms.IsArray())
        LoadShaderProgram(shaderPrograms);
}

void ShaderLoader::LoadShaders(const Value& root)
{
    ShaderStorage& storage = MainWindow::Get()->GetShaderStorage();

    auto GetShaderType = [](const std::string& typeName){
        if(typeName == "Vertex")
            return Shader::Type::Vertex;
        if(typeName == "Fragment")
            return Shader::Type::Fragment;
        if(typeName == "Geometry")
            return Shader::Type::Geometry;
        return Shader::Type::None;
    };

    for(SizeType i = 0; i < root.Size(); ++i)
    {
        auto object = root[i].GetObject();
        if(object.HasMember("Tag") &&
                object.HasMember("Type") &&
                object.HasMember("Path"))
        {
            assert(object["Tag"].IsString());
            assert(object["Type"].IsString());
            assert(object["Path"].IsString());

            storage.AddShader(object["Tag"].GetString(),
                              GetShaderType(object["Type"].GetString()),
                              object["Path"].GetString());
        }
        else
        {
            std::cout<<"Shader loading error at index = "<<i<<std::endl;
        }
    }
}

void ShaderLoader::LoadShaderProgram(const Value& root)
{
    ShaderStorage& storage = MainWindow::Get()->GetShaderStorage();

    auto GetLayoutItemType = [](const std::string& typeName){
        if(typeName == "Float")
            return ShadersLayoutItem::Type::Float;
        if(typeName == "Int")
            return ShadersLayoutItem::Type::Int;
        if(typeName == "Unsigned" ||
                typeName == "UnsignedInt" )
            return ShadersLayoutItem::Type::UnsignedInt;
        return ShadersLayoutItem::Type::None;
    };

    for(SizeType i = 0; i < root.Size(); ++i)
    {
        auto object = root[i].GetObject();
        if(object.HasMember("Tag") &&
                object.HasMember("Shaders") &&
                object.HasMember("Layout") &&
                object.HasMember("Uniforms"))
        {
            assert(object["Tag"].IsString());
            assert(object["Shaders"].IsArray());
            assert(object["Layout"].IsArray());
            assert(object["Uniforms"].IsArray());

            auto shadersArray = object["Shaders"].GetArray();
            std::vector<Shader*> shaders;
            for(SizeType j = 0; j < shadersArray.Size(); ++j)
                shaders.push_back(storage.GetShader(shadersArray[j].GetString()));

            ShadersList shadersList;
            for(auto& shader: shaders)
                shadersList[shader->GetType()] = shader;


            auto uniformsArray = object["Uniforms"].GetArray();
            std::vector<std::string> uniforms;
            for(SizeType j = 0; j < uniformsArray.Size(); ++j)
                uniforms.push_back(uniformsArray[j].GetString());

            auto program = storage.AddShaderProgram(object["Tag"].GetString(), shadersList, uniforms);

            auto layoutArray = object["Layout"].GetArray();
            ShadersLayout layout;
            for(SizeType j = 0; j < layoutArray.Size(); ++j)
                layout.Add(GetLayoutItemType(layoutArray[j]["Type"].GetString()),
                           layoutArray[j]["Count"].GetInt());

            program->SetLayout(layout);
        }
        else
        {
            std::cout<<"Shader program loading error at index = "<<i<<std::endl;
        }
    }
}
