#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "DrawableObject.h"


class PhysicsObject: public BaseObject
{
public:
    PhysicsObject();

    void Update(float dt) override;

    void SetVelocity(const glm::vec3 velocity);
    void AddVelocity(const glm::vec3 velocity);
    void DiscardVelocity();

    inline const glm::vec3& GetVelocity() { return _velocity; }


private:
    glm::vec3 _velocity;

};

#endif // PHYSICSOBJECT_H
