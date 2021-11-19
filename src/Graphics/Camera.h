#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>


class Camera
{
public:
    Camera();

    inline const glm::mat4& Projection() { return _projection; }

    void ResizeViewport(unsigned width, unsigned height);

    void SetNearPlane(float near);
    void SetFarPlane(float far);
    void SetFov(float fov);


private:
    void UpdateProjection();

    glm::mat4 _projection;

    float _aspectRatio;
    float _nearPlane;
    float _farPlane;
    float _fov;
};

#endif // CAMERA_H
