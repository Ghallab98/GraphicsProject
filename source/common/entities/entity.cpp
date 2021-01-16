#include <entities/entity.hpp>

Entity::Entity() {}

void Entity::addComponent(Component *component)
{
    if (component != nullptr)
    {
        component->setEntity(this);
        components.push_back(component);
    }
}

TransformationComponent *Entity::getTransformationComponent()
{
    for (int i = 0, numComponenets = components.size(); i < numComponenets; i++)
        if (components[i]->getComponentType() == TRANSFORMATION_COMPONENT)
            return dynamic_cast<TransformationComponent *>(components[i]);

    return nullptr;
}

CameraComponent *Entity::getCameraComponent()
{
    for (int i = 0, numComponenets = components.size(); i < numComponenets; i++)
        if (components[i]->getComponentType() == CAMERA_COMPONENT)
            return dynamic_cast<CameraComponent *>(components[i]);

    return nullptr;
}

CameraControllerComponent *Entity::getCameraComponentController()
{
    for (int i = 0, numComponenets = components.size(); i < numComponenets; i++)
        if (components[i]->getComponentType() == CONTROLLER_COMPONENT)
            return dynamic_cast<CameraControllerComponent *>(components[i]);

    return nullptr;
}

MeshRenderer *Entity::getMeshRendrer()
{
    for (int i = 0, numComponenets = components.size(); i < numComponenets; i++)
        if (components[i]->getComponentType() == MESH_RENDERER_COMPONENT)
            return dynamic_cast<MeshRenderer *>(components[i]);

    return nullptr;
}

LightComponent *Entity::getLightComponent()
{
    for (int i = 0, numComponenets = components.size(); i < numComponenets; i++)
        if (components[i]->getComponentType() == LIGHT_COMPONENT)
            return dynamic_cast<LightComponent *>(components[i]);

    return nullptr;
}

Entity::~Entity()
{
    for (int i = 0, numComponenets = components.size(); i < numComponenets; i++)
        delete components[i];

    components.clear();
}