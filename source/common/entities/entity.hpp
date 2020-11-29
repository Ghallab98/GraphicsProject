#ifndef MAIN_CHARACTER_HPP
#define MAIN_CHARACTER_HPP

#include <map>
#include "../components/transformationComponent.hpp"
#include "../components/component.hpp"

using std::map;

class Entity
{
private:
    int id;
    map<int, Component *> componentsContainer;

public:
    Entity(int id, Entity *parent) : id(id)
    {
        if (parent)
            componentsContainer[TRANFORMATION_COMPONENT] = new transformationComponent(parent->TC);
        else
            TC = new transformationComponent(nullptr);
    }

    void addComponent(int componentType, Component *component)
    {
        componentsContainer.insert(pair<int, Component *>(componentType, component));
    }

    Component *getComponent(int componentType)
    {
        return componentsContainer[componentType];
    }

    void removeComponent(int componentType)
    {
        componentsContainer.erase(componentType);
    }
}

#endif