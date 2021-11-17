#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <list>

#include "DrawableObject.h"
#include "ShaderStorage.h"

class Scene
{
public:
    Scene();
    ~Scene();

    void AddObject(DrawableObject* object);
    void Render();

    ShaderStorage& GetShaderStorage();

private:
    ShaderStorage _shaderStorage;
    std::list<DrawableObject*> _objects;
};

#endif // SCENE_H
