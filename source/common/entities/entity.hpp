#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <string.h>
using std::vector;

class Component;
class TransformationComponent;
class CameraComponent;
class CameraControllerComponent;
class MeshRenderer;
class LightComponent;
class MovementControllerComponenet;

class Entity
{
private:
    std::string entityName;
    vector<Component *> components;

public:
    Entity();

    void addComponent(Component *component);
    void setEntityName(std::string name);
    std::string getName();
    TransformationComponent *getTransformationComponent();
    CameraComponent *getCameraComponent();
    CameraControllerComponent *getCameraComponentController();
    MeshRenderer *getMeshRendrer();
    LightComponent *getLightComponent();
    MovementControllerComponenet *getMovementController();

    ~Entity();
};

#endif