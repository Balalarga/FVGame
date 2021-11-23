#include <iostream>

#include "MainWindow.h"
#include "Utils/ShaderLoader.h"
#include "Utils/ModelLoader.h"

using namespace std;


void InitObjects(MainWindow* window)
{
    Scene* scene = window->GetScene();
    ShaderStorage& shaderStorage = window->GetShaderStorage();

    scene->GetCamera().Move({0, 0, 5});

    // Then objects
    vector<float>data{
        -3, -3, 0, 1, 1, 0, 1,
        -3,  3, 0, 1, 1, 0, 1,
         3,  3, 0, 1, 0, 1, 1,
         3, -3, 0, 0, 1, 1, 1
    };

    DrawableObject* obj1 = new DrawableObject(shaderStorage.GetShaderProgram("DefaultSP"));
    obj1->SetPrimitive(DrawMode::Quads);
    obj1->Create(data);
    scene->AddObject(obj1);

    DrawableObject* obj = ModelLoader::LoadFromFile<DrawableObject>("../assets/models/sphere5.mbin",
                                                                    shaderStorage.GetShaderProgram("VoxelSP"));
    if(obj)
    {
        cout<<"Model loaded\n";
        scene->AddObject(obj);
    }
}


int main()
{
    auto* window = MainWindow::Create("FV Game", {1280, 720});

    ShaderLoader::LoadShadersFrom("../assets/shaderConfig.json");
    window->GetShaderStorage().CompileAll();

    InitObjects(window);

    window->UseImGui(true);
    window->Run();

    return 0;
}
