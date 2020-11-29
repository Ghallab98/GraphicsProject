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

class GameApplication : public gameTemp::Application
{

    gameTemp::ShaderProgram program;
    gameTemp::Mesh model;
    gameTemp::Mesh model1;
    gameTemp::Mesh model2;
    //gameTemp::Mesh model3;
    MeshRenderer Renderer1;
    MeshRenderer Renderer2;
    //std::string filePath = "C:\Users\moh_p\Desktop\GraphicsProject\source\common\Zuccarello.obj";
    std::vector<Transform> objects;

    struct
    {
        glm::vec3 eye;
        glm::vec3 center;
        glm::vec3 up;
    } camera_view;
    struct
    {
        bool is_perspective;
        // Common camera projection properties
        float near, far;
        float aspect_ratio;
        // "Perspective camera"-only properties
        float vertical_field_of_view_angle;
        // "Orthographic camera"-only properties
        float orthographic_height;
    } camera_projection;

    //std::vector<Entity*> Entities;

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

        gameTemp::mesh_utils::Cuboid(model, true);
        gameTemp::mesh_utils::Plane(model2, {1, 1}, true);
        gameTemp::mesh_utils::Sphere(model1, {32, 16}, true);
        //gameTemp::mesh_utils::loadOBJ(model3, filePath);

        objects.push_back({{0, -1, 0}, {0, 0, 0}, {7, 2, 7}});
        objects.push_back({{-2, 1, -2}, {0, 0, 0}, {2, 2, 2}});
        objects.push_back({{2, 1, -2}, {0, 0, 0}, {2, 2, 2}});
        objects.push_back({{-2, 1, 2}, {0, 0, 0}, {2, 2, 2}});
        objects.push_back({{2, 1, 2}, {0, 0, 0}, {2, 2, 2}});

        camera_view.eye = {10, 10, 10};
        camera_view.center = {0, 0, 0};
        camera_view.up = {0, 1, 0};

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        camera_projection.is_perspective = false;
        camera_projection.near = 0.1f;
        camera_projection.far = 100.0f;
        camera_projection.aspect_ratio = static_cast<float>(width) / height;
        camera_projection.vertical_field_of_view_angle = glm::pi<float>() / 2;
        camera_projection.orthographic_height = 20.0f;
        Renderer1.setProgram(&program);
        Renderer1.setMesh(&model);
        Renderer2.setProgram(&program);
        Renderer2.setMesh(&model1);
        glClearColor(0, 0, 0, 0);
    }

    void onDraw(double deltaTime) override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(program);

        program.set("tint", glm::vec4(1, 1, 1, 1));

        glm::mat4 view_matrix = glm::lookAt(camera_view.eye, camera_view.center, camera_view.up);
        glm::mat4 projection_matrix;
        if (camera_projection.is_perspective)
        {
            projection_matrix = glm::perspective(camera_projection.vertical_field_of_view_angle, camera_projection.aspect_ratio, camera_projection.near, camera_projection.far);
        }
        else
        {
            float half_height = camera_projection.orthographic_height * 0.5f;
            float half_width = camera_projection.aspect_ratio * half_height;
            projection_matrix = glm::ortho(-half_width, half_width, -half_height, half_height, camera_projection.near, camera_projection.far);
        }

        glm::mat4 camera_matrix = projection_matrix * view_matrix;
        Renderer1.Draw(camera_matrix * objects[1].to_mat4());
        Renderer2.Draw(camera_matrix * objects[2].to_mat4());
        //for(const auto& object : objects) {
        //    program.set("transform", camera_matrix * object.to_mat4());
        //    model.draw();
        //}
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

        ImGui::Begin("Camera");
        ImGui::Text("View");
        ImGui::DragFloat3("Eye", glm::value_ptr(camera_view.eye), 0.1f);
        ImGui::DragFloat3("Center", glm::value_ptr(camera_view.center), 0.1f);
        ImGui::DragFloat3("Up", glm::value_ptr(camera_view.up), 0.1f);
        ImGui::Separator();
        ImGui::Text("Projection");
        ImGui::Checkbox("Is Perspective", &camera_projection.is_perspective);
        ImGui::DragFloat("Near", &camera_projection.near, 0.1f);
        ImGui::DragFloat("Far", &camera_projection.far, 0.1f);
        ImGui::DragFloat("Aspect Ratio", &camera_projection.aspect_ratio, 0.1f);
        if (ImGui::Button("Reset Aspect Ratio"))
        {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            camera_projection.aspect_ratio = static_cast<float>(width) / height;
        }
        if (camera_projection.is_perspective)
            ImGui::DragFloat("Vertical Field of View", &camera_projection.vertical_field_of_view_angle, 0.1f);
        else
            ImGui::DragFloat("Orthographic Height", &camera_projection.orthographic_height, 0.1f);
        ImGui::End();
    }
};

int main(int argc, char **argv)
{
    return GameApplication().run();
}
#endif