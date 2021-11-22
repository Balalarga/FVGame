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
    void OnKey(int key, int scancode, int action, int mods);
    void OnMouseButton(int button, int action, int mods);
    void OnScroll(double xoffset, double yoffset);
    void OnMouseMove(double xpos, double ypos);

    inline Camera& GetCamera() { return _camera; }


private:
    Camera _camera;
    std::list<DrawableObject*> _objects;
};

#endif // SCENE_H
