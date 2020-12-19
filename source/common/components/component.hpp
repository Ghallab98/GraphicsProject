#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#define TRANSFORMATION_COMPONENT 0
#define CAMERA_COMPONENT 1
#define CONTROLLER_COMPONENT 2
#define MESH_RENDERER_COMPONENT 3

class Entity;

class Component
{
protected:
    Entity *myEntity;

public:
    Component() {}
    virtual int getComponentType() = 0;
    virtual ~Component() {}
};

#endif