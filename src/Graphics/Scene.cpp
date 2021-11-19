#include "Scene.h"

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
        obj->GetShaderProgram()->SetUniform("MVP", obj->GetTransform().Matrix() * _camera.Projection());
        obj->Render();
        obj->ReleaseShader();
    }
}

