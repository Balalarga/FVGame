#include <iostream>

#include "MainWindow.h"

using namespace std;


void InitObjects(MainWindow* window)
{
    Scene* scene = window->GetScene();
    ShaderStorage& shaderStorage = scene->GetShaderStorage();

    // Shaders first
    ShadersList shadersList1;

    shadersList1[Shader::Type::Vertex] = shaderStorage.AddShader("v_1", Shader::Type::Vertex, "../assets/shaders/default.vert");
    shadersList1[Shader::Type::Fragment] = shaderStorage.AddShader("f_1", Shader::Type::Fragment, "../assets/shaders/default.frag");

    ShadersLayout layout1;
    layout1.Add(ShadersLayoutItem::Type::Float, 3);
    layout1.Add(ShadersLayoutItem::Type::Float, 4);
    auto shaderProgram = shaderStorage.AddShaderProgram("default", shadersList1);
    shaderProgram->SetLayout(layout1);

    shaderStorage.CompileAll();

    // Then objects

    vector<float>data{
        -1, -1, 0, 1, 1, 0, 1,
        -1,  1, 0, 1, 1, 0, 1,
         1,  1, 0, 1, 0, 1, 1,
         1, -1, 0, 0, 1, 1, 1
    };

    DrawableObject* obj1 = new DrawableObject(shaderProgram);
    obj1->SetPrimitive(DrawMode::Quads);
    obj1->Create(data);
    scene->AddObject(obj1);
}


int main()
{
    auto* window = MainWindow::Create("FV Game", {1280, 720});

    InitObjects(window);

    window->UseImGui(true);
    window->Run();

    return 0;
}
