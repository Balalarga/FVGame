#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform
{
public:
    Transform();

    inline const glm::mat4& Matrix() { return _matrix; }
    inline const glm::vec3& Position() { return _position; }
    inline const glm::vec3& Rotation() { return _rotation; }
    inline const glm::vec3& Scale() { return _scale;}

    void SetPosition(const glm::vec3& newPosition);
    void SetScale(const glm::vec3& newScale);
    void SetRotation(const glm::vec3& newRotation);

    void ReScale(const glm::vec3& scale);
    void Move(const glm::vec3& position);
    void Rotate(const glm::vec3& rotation);


private:
    void UpdateMatrix();

    glm::mat4 _matrix;

    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _rotation;
};

#endif // TRANSFORM_H
