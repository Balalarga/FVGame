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

void InitInput(MainWindow* window)
{
    Scene* scene = window->GetScene();
    auto* input = InputHandler::Get();

    input->Key(GLFW_KEY_W).AddOnPress([scene](){
        scene->GetCamera().AddVelocity({0, 1, 0});
    });
    input->Key(GLFW_KEY_S).AddOnPress([scene](){
        scene->GetCamera().AddVelocity({0, -1, 0});
    });
    input->Key(GLFW_KEY_D).AddOnPress([scene](){
        scene->GetCamera().AddVelocity({1, 0, 0});
    });
    input->Key(GLFW_KEY_A).AddOnPress([scene](){
        scene->GetCamera().AddVelocity({-1, 0, 0});
    });

    input->Key(GLFW_KEY_W).AddOnRelease([scene](){
        scene->GetCamera().AddVelocity({0, -1, 0});
    });
    input->Key(GLFW_KEY_S).AddOnRelease([scene](){
        scene->GetCamera().AddVelocity({0, 1, 0});
    });
    input->Key(GLFW_KEY_D).AddOnRelease([scene](){
        scene->GetCamera().AddVelocity({-1, 0, 0});
    });
    input->Key(GLFW_KEY_A).AddOnRelease([scene](){
        scene->GetCamera().AddVelocity({1, 0, 0});
    });
}


int main()
{
    auto* window = MainWindow::Create("FV Game", {1280, 720});

    ShaderLoader::LoadShadersFrom("../assets/shaderConfig.json");
    window->GetShaderStorage().CompileAll();

    InitObjects(window);
    InitInput(window);

    window->UseImGui(true);
    window->Run();

    return 0;
}
