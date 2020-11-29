#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#define TRANFORMATION_COMPONENT 0
#define RENDER_COMPONENT 1
#define CAMERA_COMPONENT 2
#define PHYSICS_COMPONENT 3

#include "./entities/entity.hpp"
class Component
{
private:
    Entity *myEntity;

public:
    Component() {}
    virtual ~Component() {}
};

#endif