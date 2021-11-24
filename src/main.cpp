#include <iostream>

#include "MainWindow.h"
#include "Utils/ShaderLoader.h"
#include "Utils/ModelLoader.h"

using namespace std;


void InitObjects(MainWindow* window)
{
    Scene* scene = window->GetScene();
    scene->GetCamera().Move({0, 0, 4});

    ShaderStorage& shaderStorage = window->GetShaderStorage();

    DrawableObject* obj = ModelLoader::LoadRawFromFile<DrawableObject>("../assets/models/sphere3.mbin",
                                                                       shaderStorage.GetShaderProgram("VoxelSP"),
                                                                       Color::fromUint(220, 50, 50, 255));
    if(obj)
        scene->AddObject(obj);
    else
        cout<<"Couldn't load model\n";


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
