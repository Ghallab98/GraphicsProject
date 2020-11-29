#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../components/transformationComponent.hpp"
#include "../components/cameraComponent.hpp"
#include "../components/cameraControllerComponent.hpp"
#include "../components/MeshRenderer.hpp"

class Entity
{
private:
    int id;
    TransformationComponent *transform;
    CameraComponent *camera;
    CameraControllerComponent *cameraController;
    MeshRenderer *mesh;

public:
    Entity(int id) : id(id)
    {
        transform = nullptr;
        camera = nullptr;
        mesh = nullptr;
        cameraController = nullptr;
    }

    void setTransformationComponent(TransformationComponent *TC)
    {
        transform = TC;
    }

    void setCameraComponent(CameraComponent *CC)
    {
        camera = CC;
    }

    void setCameraComponentController(CameraControllerComponent *CC)
    {
        cameraController = CC;
    }

    void setMeshRendrer(MeshRenderer *MR)
    {
        mesh = MR;
    }

    TransformationComponent *getTransformationComponent()
    {
        return transform;
    }

    CameraComponent *getCameraComponent()
    {
        return camera;
    }

    CameraControllerComponent *getCameraComponentController()
    {
        return cameraController;
    }

    MeshRenderer *getMeshRendrer()
    {
        return mesh;
    }
};

#endif