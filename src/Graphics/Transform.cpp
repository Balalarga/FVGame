#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform():
    _position({0, 0, 0}),
    _scale({1, 1, 1}),
    _rotation({0, 0, 0})
{
    UpdateMatrix();
}

void Transform::SetPosition(const glm::vec3 &newPosition)
{
    _position = newPosition;
    UpdateMatrix();
}

void Transform::SetScale(const glm::vec3 &newScale)
{
    _scale = newScale;
    UpdateMatrix();
}

void Transform::SetRotation(const glm::vec3 &newRotation)
{
    _rotation = newRotation;
    UpdateMatrix();
}

void Transform::ReScale(const glm::vec3 &scale)
{
    _scale += scale;
    UpdateMatrix();
}

void Transform::Move(const glm::vec3 &position)
{
    _position += position;
    UpdateMatrix();
}

void Transform::Rotate(const glm::vec3 &rotation)
{
    _rotation += rotation;
    UpdateMatrix();
}

void Transform::UpdateMatrix()
{
    _matrix = glm::scale(glm::mat4(1.0f), _scale);
    _matrix *= glm::translate(glm::mat4(1.0f), _position);
    _matrix *= glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    _matrix *= glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    _matrix *= glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.z), glm::vec3(0, 0, 1));
}
