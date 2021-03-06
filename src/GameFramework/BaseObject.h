#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Input/InputHandler.h"


class BaseObject
{
public:
    BaseObject();
    virtual ~BaseObject() = default;

    virtual void Update(float dt) {}

    inline const glm::mat4& Transform()   { return _matrix; }
    inline const glm::vec3& GetPosition() { return _position; }
    inline const glm::vec3& GetRotation() { return _rotation; }
    inline const glm::vec3& GetScale()    { return _scale; }

    void SetPosition(const glm::vec3& newPosition);
    void SetScale(const glm::vec3& newScale);
    void SetRotation(const glm::vec3& newRotation);

    void Scale(const glm::vec3& dScale);
    void Move(const glm::vec3& dPosition);
    void Rotate(const glm::vec3& dRotation);


protected:
    virtual void UpdateMatrix();


private:
    glm::mat4 _matrix;

    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _rotation;
};

#endif // BASEOBJECT_H
