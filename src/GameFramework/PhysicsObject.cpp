#include "PhysicsObject.h"


PhysicsObject::PhysicsObject():
    _velocity(glm::vec3(0.f))
{

}

void PhysicsObject::Update(float dt)
{
    if(_velocity.x != 0 || _velocity.y != 0 || _velocity.z != 0)
        Move(_velocity * dt);
}

void PhysicsObject::SetVelocity(const glm::vec3 velocity)
{
    _velocity = velocity;
}

void PhysicsObject::AddVelocity(const glm::vec3 velocity)
{
    _velocity += velocity;
}

void PhysicsObject::DiscardVelocity()
{
    _velocity = glm::vec3(0.f);
}
