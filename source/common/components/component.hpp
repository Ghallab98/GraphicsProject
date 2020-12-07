#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../entities/entity.hpp"

class Component
{
protected:
    Entity *myEntity;

public:
    Component() {}
    virtual ~Component() {}
};

#endif