#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <list>

#include "DrawableObject.h"
#include "ShaderStorage.h"
#include "Camera.h"

class Scene
{
public:
    Scene();
    ~Scene();

    void AddObject(DrawableObject* object);
    void Render();

    inline ShaderStorage& GetShaderStorage() { return _shaderStorage; }
    inline Camera& GetCamera() { return _camera; }

private:
    Camera _camera;
    ShaderStorage _shaderStorage;
    std::list<DrawableObject*> _objects;
};

#endif // SCENE_H
