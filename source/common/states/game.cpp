#ifndef GAME_STATE
#define GAME_STATE

#include <application.hpp>
#include <shader.hpp>
#include <imgui-utils/utils.hpp>
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>

#include "./entities/entity.hpp"

#include <MeshRenderer.hpp>
#include <cameraComponent.hpp>
#include <cameraControllerComponent.hpp>
#include <transformationComponent.hpp>

#include "../Renderer/RendererSystem.hpp"

class GameState : public gameTemp::Application
{
    gameTemp::ShaderProgram program;
    gameTemp::Mesh model, model1;

    Entity myCamera;
    Entity *cubeParent = new Entity;
    Entity *cubeChild = new Entity;
    Entity *sphere = new Entity;

    vector<Entity *> Entities;
    RendererSystem rendererSystem;

    gameTemp::WindowConfiguration getWindowConfiguration() override
    {
        return {"Game State", {1280, 720}, false};
    }

    void onInitialize() override
    {
        program.create();
        program.attach("assets/shaders/transform.vert", GL_VERTEX_SHADER);
        program.attach("assets/shaders/tint.frag", GL_FRAGMENT_SHADER);
        program.link();

        // -- Initializing mesh components
        gameTemp::mesh_utils::Cuboid(model, true);
        gameTemp::mesh_utils::Sphere(model1, {32, 16}, true);
        gameTemp::Mesh *ptrCube;
        gameTemp::Mesh *ptrSphere;
        gameTemp::ShaderProgram *ptrShader;

        ptrCube = &model;
        ptrSphere = &model1;
        ptrShader = &program;

        MeshRenderer *meshCubeParent = new MeshRenderer(ptrCube, ptrShader);
        MeshRenderer *meshCubeChild = new MeshRenderer(ptrCube, ptrShader);
        MeshRenderer *meshSPhere = new MeshRenderer(ptrSphere, ptrShader);

        cubeParent->setMeshRendrer(meshCubeParent);
        cubeChild->setMeshRendrer(meshCubeChild);
        sphere->setMeshRendrer(meshSPhere);

        // -- Initializing transformation components
        TransformationComponent *TCcubeParent = new TransformationComponent(nullptr);
        TransformationComponent *TCcubeChild = new TransformationComponent(TCcubeParent);
        TransformationComponent *TCSphere = new TransformationComponent(TCcubeChild);

        TCcubeParent->transform({-2, 1, -2}, {0, 0, 0}, {2, 2, 2});
        TCcubeChild->transform({2, 2, -2}, {0, 0, 0}, {1, 1, 1});
        TCSphere->transform({-2, 1, 2}, {0, 0, 0}, {2, 2, 2});

        cubeParent->setTransformationComponent(TCcubeParent);
        cubeChild->setTransformationComponent(TCcubeChild);
        sphere->setTransformationComponent(TCSphere);

        // -- Storing entities
        Entities.push_back(cubeParent);
        Entities.push_back(cubeChild);
        Entities.push_back(sphere);

        // -- Initializing the camera
        CameraComponent *Cam = new CameraComponent;
        myCamera.setCameraComponent(Cam);
        Cam->setEyePosition({10, 10, 10});
        Cam->setTarget({0, 0, 0});
        Cam->setUp({0, 1, 0});

        CameraControllerComponent *CamController = new CameraControllerComponent(this, &myCamera);
        myCamera.setCameraControllerComponent(CamController);

        // -- Initializing the renderer
        rendererSystem.setEntitiesVector(&Entities);

        // -- GL options
        glEnable(GL_CULL_FACE);
        glClearColor(0, 0, 0, 0);
    }

    void onDraw(double deltaTime) override
    {
        if (keyboard.isPressed(GLFW_KEY_ESCAPE))
            this->nextStateId = MENU_STATE_ID;

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        program.set("tint", glm::vec4(1, 1, 1, 1));

        ///////////////// INFO: PROTOTYPING BLOCK
        glm::vec3 translation_sensitivity = {20.0f, 20.0f, 20.0f};
        glm::vec3 translation;

        if (getKeyboard().justReleased(GLFW_KEY_I))
        {
            translation = {0.0f, 0.0f, (float)deltaTime * translation_sensitivity.z};
            cubeParent->getTransformationComponent()->transform(translation);
        }
        if (getKeyboard().justReleased(GLFW_KEY_K))
        {
            translation = {0.0f, 0.0f, (float)deltaTime * translation_sensitivity.z * -1};
            cubeParent->getTransformationComponent()->transform(translation);
        }
        if (getKeyboard().justReleased(GLFW_KEY_L))
        {
            translation = {(float)deltaTime * translation_sensitivity.x, 0.0f, 0.0f};
            cubeParent->getTransformationComponent()->transform(translation);
        }
        if (getKeyboard().justReleased(GLFW_KEY_J))
        {
            translation = {(float)deltaTime * translation_sensitivity.x * -1, 0.0f, 0.0f};
            cubeParent->getTransformationComponent()->transform(translation);
        }
        if (getKeyboard().justReleased(GLFW_KEY_O))
        {
            translation = {(float)deltaTime * translation_sensitivity.x, 0.0f, 0.0f};
            sphere->getTransformationComponent()->transform(translation);
        }
        if (getKeyboard().justReleased(GLFW_KEY_P))
        {
            translation = {(float)deltaTime * translation_sensitivity.x * -1, 0.0f, 0.0f};
            sphere->getTransformationComponent()->transform(translation);
        }
        ///////////////// END PROTOTYPING

        myCamera.getCameraComponentController()->update(deltaTime);
        glm::mat4 camera_matrix = myCamera.getCameraComponent()->getVPMatrix();

        rendererSystem.update(camera_matrix);
    }

    void onDestroy() override
    {
        program.destroy();
        model.destroy();
    }
};

#endif