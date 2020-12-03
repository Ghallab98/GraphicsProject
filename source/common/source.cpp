#ifndef SOURCE
#define SOURCE
#include <application.hpp>
#include <shader.hpp>
#include <imgui-utils/utils.hpp>
#include "./entities/entity.hpp"
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>
#include "../common/components/MeshRenderer.hpp"
#include <glm/gtx/euler_angles.hpp>
#include "./components/cameraComponent.hpp"
#include "./components/cameraControllerComponent.hpp"

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

class CameraProjectionApplication : public gameTemp::Application
{

    gameTemp::ShaderProgram program;
    gameTemp::Mesh model;
    Entity myCamera;
    std::vector<Transform> objects;

    gameTemp::WindowConfiguration getWindowConfiguration() override
    {
        return {"Projection", {1280, 720}, false};
    }

    void onInitialize() override
    {
        program.create();
        program.attach("assets/shaders/transform.vert", GL_VERTEX_SHADER);
        program.attach("assets/shaders/tint.frag", GL_FRAGMENT_SHADER);
        program.link();

        // Populate model intance with cuboid data.
        gameTemp::mesh_utils::Cuboid(model, true);

        // Array of transforms to draw the same cuboid with different (position/rotation/scale).
        objects.push_back({{0, -1, 0}, {0, 0, 0}, {7, 2, 7}});
        objects.push_back({{-2, 1, -2}, {0, 0, 0}, {2, 2, 2}});
        objects.push_back({{2, 1, -2}, {0, 0, 0}, {2, 2, 2}});
        objects.push_back({{-2, 1, 2}, {0, 0, 0}, {2, 2, 2}});
        objects.push_back({{2, 1, 2}, {0, 0, 0}, {2, 2, 2}});

   
    
        CameraComponent *Cam = new CameraComponent;
        myCamera.setCameraComponent(Cam);

        Cam->setEyePosition({10, 10, 10});
        Cam->setTarget({0, 0, 0});
        Cam->setUp({0, 1, 0});

        CameraControllerComponent *CamController = new CameraControllerComponent(this, &myCamera);
        myCamera.setCameraControllerComponent(CamController);

        glClearColor(0, 0, 0, 0);
    }

    void onDraw(double deltaTime) override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);

        program.set("tint", glm::vec4(1, 1, 1, 1));

        myCamera.getCameraComponentController()->update(deltaTime);
        glm::mat4 camera_matrix = myCamera.getCameraComponent()->getVPMatrix();

        // We use the created camera matrix to render the object.
        for (const auto &object : objects)
        {
            program.set("transform", camera_matrix * object.to_mat4());
            model.draw();
        }
    }

    void onDestroy() override
    {
        program.destroy();
        model.destroy();
    }

    void onImmediateGui(ImGuiIO &io) override
    {

        ImGui::Begin("Objects");

        gameTemp::ReorderableList(
            objects.begin(), objects.end(),
            [](size_t index, Transform &transform) {
                ImGui::DragFloat3("Translation", glm::value_ptr(transform.translation), 1.0f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), 0.1f);
                ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);
            },
            [this](size_t index) {
                objects.insert(objects.begin() + index, Transform());
            },
            [this](size_t index) {
                objects.erase(objects.begin() + index);
            });

        ImGui::End();
    }
};

int main(int argc, char **argv)
{
    return CameraProjectionApplication().run();
}
#endif