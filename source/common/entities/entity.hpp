#ifndef ENTITY_HPP
#define ENTITY_HPP

class TransformationComponent;
class CameraComponent;
class CameraControllerComponent;
class MeshRenderer;

class Entity
{
private:
    TransformationComponent *transformComponent;
    CameraComponent *cameraComponent;
    CameraControllerComponent *cameraController;
    MeshRenderer *mesh;

public:
    Entity()
    {
        transformComponent = nullptr;
        cameraComponent = nullptr;
        mesh = nullptr;
        cameraController = nullptr;
    }

    void setTransformationComponent(TransformationComponent *TC)
    {
        transformComponent = TC;
    }

    void setCameraComponent(CameraComponent *CC)
    {
        cameraComponent = CC;
    }

    void setCameraControllerComponent(CameraControllerComponent *CC)
    {
        cameraController = CC;
    }

    void setMeshRendrer(MeshRenderer *MR)
    {
        mesh = MR;
    }

    TransformationComponent *getTransformationComponent()
    {
        return transformComponent;
    }

    CameraComponent *getCameraComponent()
    {
        return cameraComponent;
    }

    CameraControllerComponent *getCameraComponentController()
    {
        return cameraController;
    }

    MeshRenderer *getMeshRendrer()
    {
        return mesh;
    }

    ~Entity()
    {
        if (transformComponent)
            delete transformComponent;

        if (cameraComponent)
            delete cameraComponent;

        if (cameraController)
            delete cameraController;

        if (mesh)
            delete mesh;
    }
};

#endif