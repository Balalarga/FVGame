#include "Scene.h"

#include <iostream>
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
        obj->BindShader();
        obj->GetShaderProgram()->SetUniform("MVP", mvp);
        obj->Render();
        obj->ReleaseShader();
    }
}

