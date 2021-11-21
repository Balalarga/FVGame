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
    glm::mat4 pv = _camera.Projection() * glm::inverse(_camera.GetTransform().Matrix());
    for(auto& obj: _objects)
    {
        glm::mat4 mvp =  pv * obj->GetTransform().Matrix();
        obj->BindShader();
        obj->GetShaderProgram()->SetUniform("MVP", mvp);
        obj->Render();
        obj->ReleaseShader();
    }
}

