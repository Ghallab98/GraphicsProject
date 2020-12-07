#ifndef ENTITY_HPP
#define ENTITY_HPP

class TransformationComponent;
class CameraComponent;
class CameraControllerComponent;
class MeshRenderer;

class Entity
{
private:
    TransformationComponent *transform;
    CameraComponent *camera;
    CameraControllerComponent *cameraController;
    MeshRenderer *mesh;

public:
    Entity()
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