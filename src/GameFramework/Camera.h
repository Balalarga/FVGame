#ifndef CAMERA_H
#define CAMERA_H

#include "PhysicsObject.h"

class Camera: public PhysicsObject
{
public:
    Camera();

    inline const glm::mat4& ViewProject() { return _viewProjMatrix; }
    inline const glm::mat4& Project() { return _projection; }
    inline glm::mat4 View() { return glm::inverse(Transform()); }

    void ResizeViewport(unsigned width, unsigned height);
    void SetNearPlane(float near);
    void SetFarPlane(float far);
    void SetFov(float fov);


protected:
    virtual void UpdateMatrix() override;


private:
    void UpdataViewProjection();
    void UpdateProjection();

    glm::mat4 _projection;
    glm::mat4 _viewProjMatrix;

    float _aspectRatio;
    float _nearPlane;
    float _farPlane;
    float _fov;
};

#endif // CAMERA_H
