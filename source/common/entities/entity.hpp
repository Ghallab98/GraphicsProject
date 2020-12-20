#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
using std::vector;

#include"./objectProperties.cpp"

class Component;
class TransformationComponent;
class CameraComponent;
class CameraControllerComponent;
class MeshRenderer;



class Entity
{
private:
    vector<Component *> components;
    ObjectProperties objProp;

public:
    Entity();

    void addComponent(Component *component);
    TransformationComponent *getTransformationComponent();
    CameraComponent *getCameraComponent();
    CameraControllerComponent *getCameraComponentController();
    MeshRenderer *getMeshRendrer();
    ObjectProperties* getObjProp();
    void setCullObjProp(Culling * myCull);
    void setBlendObjProp(Blending * myBlend);


    ~Entity();
};

#endif