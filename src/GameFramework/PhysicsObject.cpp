#include "PhysicsObject.h"

#include <iostream>

PhysicsObject::PhysicsObject():
    _velocity(glm::vec3(0.f))
{

}

void PhysicsObject::Update(float dt)
{
//    std::cout<<"AdUpdate: \n"<<_velocity.x<<", "<<_velocity.y<<", "<<_velocity.z<<"\n";
    if(_velocity.x != 0.f || _velocity.y != 0.f || _velocity.z != 0.f)
        Move(_velocity * dt);
}

void PhysicsObject::SetVelocity(const glm::vec3& velocity)
{
    _velocity = velocity;
//    std::cout<<"SetVel\n";
}

void PhysicsObject::AddVelocity(const glm::vec3& velocity)
{
    _velocity += velocity;
//    std::cout<<"AddVel: \n"<<_velocity.x<<", "<<_velocity.y<<", "<<_velocity.z<<"\n";
}

void PhysicsObject::DiscardVelocity()
{
    _velocity = glm::vec3(0.f);
//    std::cout<<"DiscVel\n";
}
