#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <list>

#include "Camera.h"
#include "DrawableObject.h"


class Scene
{
public:
    Scene();
    ~Scene();

    void AddObject(DrawableObject* object);
    void Render();

    void Update(float dt);
    void OnWindowResize(int width, int height);
    void OnViewportResize(int width, int height);

    inline Camera& GetCamera() { return _camera; }


private:
    Camera _camera;
    std::list<DrawableObject*> _objects;
};

#endif // SCENE_H
