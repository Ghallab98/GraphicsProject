#ifndef GAMESTATE
#define GAMESTATE
#include <application.hpp>
#include <shader.hpp>
#include <imgui-utils/utils.hpp>
#include "./entities/entity.hpp"
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>

#include "../common/components/MeshRenderer.hpp"
#include "./components/cameraComponent.hpp"
#include "./components/cameraControllerComponent.hpp"
#include "./components/transformationComponent.hpp"


#include <iostream>
using namespace std;

struct Transform
 {
     glm::vec3 translation, rotation, scale;

     Transform(
         const glm::vec3 &translation = {0, 0, 0},
         const glm::vec3 &rotation = {0, 0, 0},
         const glm::vec3 &scale = {1, 1, 1}) : translation(translation), rotation(rotation), scale(scale) {}

     glm::mat4 to_mat4() const
     {
         return glm::translate(glm::mat4(1.0f), translation) *
                glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
                glm::scale(glm::mat4(1.0f), scale);
     }
 };

class GameState : public gameTemp::Application
{
    gameTemp::ShaderProgram program;
    gameTemp::Mesh model, model1;
    Entity myCamera;

    Entity *cubeParent = new Entity(0);
    Entity *cubeChild = new Entity(1); //child of cube parent , should send the transformation component of the cubeparent in the TC of cubechild
    Entity *sphere = new Entity(2);

    std::vector<Transform> objects;
    vector<Entity *> EntitiesContainer;

    TransformationComponent *TCSphere;
    TransformationComponent *TCcubeChild;
    TransformationComponent *TCcubeParent;

    gameTemp::WindowConfiguration getWindowConfiguration() override
    {
        return {"GameState", {1280, 720}, false};
    }

    void rendererSystem(vector<Entity*>& Entities, glm::mat4 cameraMatrix)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        for(int i=0;i<Entities.size();i++)
        {
            if(Entities[i]->getMeshRendrer()){
                TransformationComponent *TC = Entities[i]->getTransformationComponent();
                glm::mat4 transformationMatrix = TC->getTransformationMatrix();
                MeshRenderer* R = Entities[i]->getMeshRendrer();
                glm::mat4 matrix = cameraMatrix *transformationMatrix;
                R->Draw(matrix);
            }
        }
    }
    void onInitialize() override
    {
        program.create();
        program.attach("assets/shaders/transform.vert", GL_VERTEX_SHADER);
        program.attach("assets/shaders/tint.frag", GL_FRAGMENT_SHADER);
        program.link();
        gameTemp::mesh_utils::Cuboid(model, true);           
        gameTemp::mesh_utils::Sphere(model1, {32, 16}, true);
        gameTemp::Mesh* ptrCube;
        gameTemp::Mesh* ptrSphere;
        gameTemp::ShaderProgram* ptrShader;

        ptrCube = &model;
        ptrSphere =&model1;
        ptrShader =&program;

        MeshRenderer *meshCubeParent = new MeshRenderer(ptrCube,ptrShader);
        MeshRenderer *meshCubeChild = new MeshRenderer(ptrCube,ptrShader);
        MeshRenderer *meshSPhere = new MeshRenderer(ptrSphere,ptrShader);

        TCcubeParent = new TransformationComponent(nullptr);
        TCcubeChild = new TransformationComponent(TCcubeParent);
        TCSphere = new TransformationComponent(nullptr);


        objects.push_back({ {-2,1,-2}, {0,0,0}, {2,2,2} });
        objects.push_back({ {2,1,-2}, {0,0,0}, {2,2,2} });
        objects.push_back({ {-2,1,2}, {0,0,0}, {2,2,2} });

        TCcubeParent->transform(objects[0].translation,objects[0].rotation,objects[0].scale);
        TCcubeChild->transform(objects[1].translation,objects[1].rotation,objects[1].scale);
        TCSphere->transform(objects[2].translation,objects[2].rotation,objects[2].scale);

        cubeParent->setTransformationComponent(TCcubeParent);
        cubeChild->setTransformationComponent(TCcubeChild);
        sphere->setTransformationComponent(TCSphere);


        cubeParent->setMeshRendrer(meshCubeParent);
        cubeChild->setMeshRendrer(meshCubeChild);
        sphere->setMeshRendrer(meshSPhere);

        // Populate model instance with cuboid data.
        EntitiesContainer.push_back(cubeParent);
        EntitiesContainer.push_back(cubeChild);
        EntitiesContainer.push_back(sphere);

        CameraComponent *Cam = new CameraComponent;
        myCamera.setCameraComponent(Cam);
        Cam->setEyePosition({10, 10, 10});
        Cam->setTarget({0, 0, 0});
        Cam->setUp({0, 1, 0});
        CameraControllerComponent *CamController = new CameraControllerComponent(this, &myCamera);
        myCamera.setCameraControllerComponent(CamController);
        glEnable(GL_CULL_FACE);
        glClearColor(0, 0, 0, 0);
    }

    void onDraw(double deltaTime) override
    {
        if (keyboard.isPressed(GLFW_KEY_ESCAPE))
        {
            this->nextStateId = MENU_STATE_ID;
        }
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        program.set("tint", glm::vec4(1, 1, 1, 1));

        myCamera.getCameraComponentController()->update(deltaTime);
        glm::mat4 camera_matrix = myCamera.getCameraComponent()->getVPMatrix();

        TCcubeParent->transform(objects[0].translation,objects[0].rotation,objects[0].scale);
        TCcubeChild->transform(objects[1].translation,objects[1].rotation,objects[1].scale);
        TCSphere->transform(objects[2].translation,objects[2].rotation,objects[2].scale);



        // We use the created camera matrix to render the object.
        rendererSystem(EntitiesContainer,camera_matrix);
    }

    void onDestroy() override
    {
        program.destroy();
        model.destroy();
    }

     void onImmediateGui(ImGuiIO &io) override
     {

         ImGui::Begin("Entities");
       
       
       
         gameTemp::ReorderableList(objects.begin(), objects.end(),[](size_t index, Transform& transform)
         {
             ImGui::DragFloat3("Translation", glm::value_ptr(transform.translation), 1.0f);
             ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), 0.1f);
             ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);
         },
         [this](size_t index){
                    objects.insert(objects.begin() + index, Transform());
         },
         [this](size_t index){
                     objects.erase(objects.begin() + index);
         });
         
         ImGui::End();
     }
};
#endif