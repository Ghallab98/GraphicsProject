#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#define TRANSFORMATION_COMPONENT 0
#define CAMERA_COMPONENT 1
#define CONTROLLER_COMPONENT 2
#define MESH_RENDERER_COMPONENT 3
#define LIGHT_COMPONENT 4

class Entity;

class Component
{
protected:
    Entity *myEntity;

public:
    Component() {}
    virtual ~Component() {}
    virtual int getComponentType() = 0;

    void setEntity(Entity *entity)
    {
        myEntity = entity;
    }
};

#endif