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
        obj->BindShader();
        obj->GetShaderProgram()->SetUniform("ModelMatrix", obj->Transform());
        obj->GetShaderProgram()->SetUniform("ViewMatrix", _camera.View());
        obj->GetShaderProgram()->SetUniform("ProjectionMatrix", _camera.Project());
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
