#ifndef STATE_CPP
#define STATE_CPP

#include <string>
using std::string;

#include <shader.hpp>
#include <imgui-utils/utils.hpp>
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>

#include <entities/entity.hpp>
#include <MeshRenderer.hpp>
#include <cameraComponent.hpp>
#include <cameraControllerComponent.hpp>
#include <transformationComponent.hpp>
#include <light.hpp>
#include <movemenetController.hpp>
#include <movemenetController.cpp>
#include <entities/entity.cpp>

#include <application.hpp>
using gameTemp::Application;

class State
{
protected:
    map<string, gameTemp::ShaderProgram> programs;
    Application *app;
    string name;

public:
    State(Application *app = nullptr)
    {
        this->app = app;
    }

    virtual void onEnter() = 0;
    virtual void onDraw(double deltaTime) = 0;

    virtual void onExit()
    {
        // Destroy shader programs
        for (auto it = programs.begin(); it != programs.end(); ++it)
            it->second.destroy();

        programs.clear();

        // Clear screen
        glClearColor(0, 0, 0, 0);
    }

    string getName()
    {
        return name;
    }
};

#endif