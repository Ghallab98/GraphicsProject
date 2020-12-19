#ifndef GAME_STATE_CPP
#define GAME_STATE_CPP

#include <map>
using std::map;

#include <states/state.cpp>
#include <Renderer/RendererSystem.hpp>

#define PI 3.1415926535897932384626433832795

class GameState : public State
{
    map<string, gameTemp::Mesh> models;
    vector<Entity *> entities;
    Entity *currentCamera;
    RendererSystem rendererSystem;

public:
    GameState(Application *app = nullptr) : State(app)
    {
        name = "GameState";
    }

    void onEnter() override
    {
        // -- Initializing shaders
        programs["main"].create();
        programs["main"].attach("assets/shaders/transform.vert", GL_VERTEX_SHADER);
        programs["main"].attach("assets/shaders/tint.frag", GL_FRAGMENT_SHADER);
        programs["main"].link();

        // -- Initializing entities
        Entity *cubeParent = new Entity;
        Entity *cubeChild = new Entity;
        Entity *sphere = new Entity;

        // -- Initializing mesh components
        gameTemp::mesh_utils::Cuboid(models["cuboid"], true);
        gameTemp::mesh_utils::Sphere(models["sphere"], {32, 16}, true);
        cubeParent->addComponent(new MeshRenderer(&models["cuboid"], &programs["main"]));
        cubeChild->addComponent(new MeshRenderer(&models["cuboid"], &programs["main"]));
        sphere->addComponent(new MeshRenderer(&models["sphere"], &programs["main"]));

        // -- Initializing transformation components
        TransformationComponent *TCcubeParent = new TransformationComponent(nullptr);
        TransformationComponent *TCcubeChild = new TransformationComponent(TCcubeParent);
        TransformationComponent *TCSphere = new TransformationComponent(TCcubeChild);

        cubeParent->addComponent(TCcubeParent);
        cubeChild->addComponent(TCcubeChild);
        sphere->addComponent(TCSphere);

        cubeParent->getTransformationComponent()->transform({-2, 1, -2}, {0, 0, 0}, {2, 2, 2});
        cubeChild->getTransformationComponent()->transform({2, 2, -2}, {0, 0, 0}, {1, 1, 1});
        sphere->getTransformationComponent()->transform({-2, 1, 2}, {0, 0, 0}, {2, 2, 2});

        // -- Storing entities
        entities.push_back(cubeParent);
        entities.push_back(cubeChild);
        entities.push_back(sphere);

        // -- Initializing the camera
        CameraComponent *Cam = new CameraComponent;
        currentCamera = new Entity;
        currentCamera->addComponent(Cam);
        Cam->setEyePosition({10, 10, 10});
        Cam->setTarget({0, 0, 0});
        Cam->setUp({0, 1, 0});

        glUseProgram(programs["main"]);
        CameraControllerComponent *CamController = new CameraControllerComponent(app, currentCamera);
        currentCamera->addComponent(CamController);

        // -- Initializing GL
        programs["main"].set("tint", glm::vec4(1, 1, 1, 1));
        rendererSystem.setEntitiesVector(&entities);
    }

    void onDraw(double deltaTime) override
    {
        currentCamera->getCameraComponentController()->update(deltaTime);
        glm::mat4 camera_matrix = currentCamera->getCameraComponent()->getVPMatrix();
        rendererSystem.update(camera_matrix);
    }

    void onExit() override
    {
        // Destroy entities
        for (int i = 0; i < entities.size(); i++)
            delete entities[i];

        entities.clear();

        // Destory mesh models
        for (auto it = models.begin(); it != models.end(); ++it)
            it->second.destroy();

        models.clear();

        State::onExit();
    }
};

#endif