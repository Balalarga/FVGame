#include "Scene.h"

#include <iostream>
using namespace std;

#include <glm/gtc/matrix_transform.hpp>

Scene::Scene()
{

}

Scene::~Scene()
{
    for(auto& obj: _objects)
        delete obj;
}

void Scene::AddObject(DrawableObject *object)
{
    _objects.push_back(object);
}

void Scene::Render()
{
    for(auto& obj: _objects)
    {
        glm::mat4 mvp =  _camera.ViewProject() * obj->Transform();
//        cout<<transform[0][0]<<", "<<transform[0][1]<<", "<<transform[0][2]<<", "<<transform[0][3]<<"\n";
//        cout<<transform[1][0]<<", "<<transform[1][1]<<", "<<transform[1][2]<<", "<<transform[1][3]<<"\n";
//        cout<<transform[2][0]<<", "<<transform[2][1]<<", "<<transform[2][2]<<", "<<transform[2][3]<<"\n";
//        cout<<transform[3][0]<<", "<<transform[3][1]<<", "<<transform[3][2]<<", "<<transform[3][3]<<"\n\n";
        obj->BindShader();
        obj->GetShaderProgram()->SetUniform("MVP", mvp);
        obj->Render();
        obj->ReleaseShader();
    }
}

void Scene::Update(float dt)
{
    _camera.Update(dt);

    for(auto& obj: _objects)
        obj->Update(dt);
}

void Scene::OnViewportResize(int width, int height)
{
    _camera.ResizeViewport(width, height);
}

void Scene::OnWindowResize(int width, int height)
{

}

void Scene::OnKey(int key, int scancode, int action, int mods)
{
    _camera.OnKey(key, scancode, action, mods);

    for(auto& obj: _objects)
        obj->OnKey(key, scancode, action, mods);
}

void Scene::OnMouseButton(int button, int action, int mods)
{
    _camera.OnMouseButton(button, action, mods);

    for(auto& obj: _objects)
        obj->OnMouseButton(button, action, mods);
}

void Scene::OnScroll(double xoffset, double yoffset)
{
    _camera.OnScroll(xoffset, yoffset);

    for(auto& obj: _objects)
        obj->OnScroll(xoffset, yoffset);
}

void Scene::OnMouseMove(double xpos, double ypos)
{
    _camera.OnMouseMove(xpos, ypos);

    for(auto& obj: _objects)
        obj->OnMouseMove(xpos, ypos);
}

