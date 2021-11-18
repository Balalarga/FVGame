#include "ShaderLoader.h"

#include <assert.h>


#include "MainWindow.h"
#include "Files.h"
#include "rapidjson/document.h"

using namespace rapidjson;

void ShaderLoader::ReadShaders(const std::string &pathToJson)
{
    Document document;
    document.Parse(Files::ReadFile(pathToJson).c_str());
    assert(document.IsObject());
    auto doc = document.GetObject();
    assert(doc.HasMember("Shaders"));
    assert(doc.HasMember("ShaderPrograms"));

    auto shaders = doc["Shaders"].GetArray();
    auto shaderPrograms = doc["ShaderPrograms"].GetArray();

    ShaderStorage& storage = MainWindow::Get()->GetScene()->GetShaderStorage();

    for(auto& i: shaders)
    {

    }


}
