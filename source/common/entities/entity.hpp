#ifndef MAIN_CHARACTER_HPP
#define MAIN_CHARACTER_HPP

#include <map>
#include <string>
#include "../components/transformationComponent.hpp"
#include "../components/component.hpp"

using std::map;

#define CUBOID 0
#define PLANE 1
#define SPHERE 2
#define OTHER 3

class Entity
{
private:
    int id;
    std::string filePath;
    int myType;
    map<int, Component *> componentsContainer;

public:
    Entity(int id, Entity *parent, int entityType, std::string file = "") : id(id), myType(entityType), filePath(file)
    {
        componentsContainer[TRANFORMATION_COMPONENT] =
            new transformationComponent(parent->getComponent(TRANFORMATION_COMPONENT));
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