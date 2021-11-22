#include "Camera.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera():
    _fov(45.f),
    _farPlane(1000.f),
    _nearPlane(.1f),
    _aspectRatio(1.f)
{
    UpdateProjection();
}

void Camera::ResizeViewport(unsigned width, unsigned height)
{
    _aspectRatio = static_cast<float>(width) /
            static_cast<float>(height);
    UpdateProjection();
}

void Camera::SetNearPlane(float near)
{
    _nearPlane = near;
    UpdateProjection();
}

void Camera::SetFarPlane(float far)
{
    _farPlane = far;
    UpdateProjection();
}

void Camera::SetFov(float fov)
{
    _fov = fov;
    UpdateProjection();
}

void Camera::UpdateMatrix()
{
    BaseObject::UpdateMatrix();
    UpdataViewProjection();
}

void Camera::UpdataViewProjection()
{
    _viewProjMatrix = _projection * glm::inverse(Transform());
}

void Camera::UpdateProjection()
{
    _projection = glm::perspective(_fov, _aspectRatio, _nearPlane, _farPlane);
    UpdataViewProjection();
}
