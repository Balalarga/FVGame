#include "BaseObject.h"

#include <glm/gtc/matrix_transform.hpp>


BaseObject::BaseObject():
    _position({0, 0, 0}),
    _scale({1, 1, 1}),
    _rotation({0, 0, 0})
{
    UpdateMatrix();
}

void BaseObject::SetPosition(const glm::vec3 &newPosition)
{
    _position = newPosition;
    UpdateMatrix();
}

void BaseObject::SetScale(const glm::vec3 &newScale)
{
    _scale = newScale;
    UpdateMatrix();
}

void BaseObject::SetRotation(const glm::vec3 &newRotation)
{
    _rotation = newRotation;
    UpdateMatrix();
}

void BaseObject::Scale(const glm::vec3 &dScale)
{
    _scale += dScale;
    UpdateMatrix();
}

void BaseObject::Move(const glm::vec3 &dPosition)
{
    _position += dPosition;
    UpdateMatrix();
}

void BaseObject::Rotate(const glm::vec3 &dRotation)
{
    _rotation += dRotation;
    UpdateMatrix();
}

void BaseObject::UpdateMatrix()
{
    _matrix = glm::translate(glm::mat4(1.0f), _position);
    _matrix = glm::scale(_matrix, _scale);
    _matrix = glm::rotate(_matrix, _rotation.x, {1, 0, 0});
    _matrix = glm::rotate(_matrix, _rotation.y, {0, 1, 0});
    _matrix = glm::rotate(_matrix, _rotation.z, {0, 0, 1});
}
