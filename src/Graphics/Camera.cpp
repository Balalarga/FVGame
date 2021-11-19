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

void Camera::UpdateProjection()
{
//    std::cout<<"Aspect :"<<_aspectRatio<<std::endl;
//    std::cout<<"Near :"<<_nearPlane<<std::endl;
//    std::cout<<"Far :"<<_farPlane<<std::endl;
    _projection = glm::perspective(_fov, _aspectRatio, _nearPlane, _farPlane);

//    std::cout<<""<<_projection[0][0]<<", "<<_projection[0][1]<<", "<<_projection[0][2]<<", "<<_projection[0][3]<<std::endl;
//    std::cout<<""<<_projection[1][0]<<", "<<_projection[1][1]<<", "<<_projection[1][2]<<", "<<_projection[1][3]<<std::endl;
//    std::cout<<""<<_projection[2][0]<<", "<<_projection[2][1]<<", "<<_projection[2][2]<<", "<<_projection[2][3]<<std::endl;
//    std::cout<<""<<_projection[3][0]<<", "<<_projection[3][1]<<", "<<_projection[3][2]<<", "<<_projection[3][3]<<std::endl;
//    std::cout<<std::endl;
}
