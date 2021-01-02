#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
using std::vector;


class Component;
class TransformationComponent;
class CameraComponent;
class CameraControllerComponent;
class MeshRenderer;


class Entity
{
private:
    vector<Component *> components;

public:
    Entity();

    void addComponent(Component *component);
    TransformationComponent *getTransformationComponent();
    CameraComponent *getCameraComponent();
    CameraControllerComponent *getCameraComponentController();
    MeshRenderer *getMeshRendrer();
    ~Entity();
};

#endif