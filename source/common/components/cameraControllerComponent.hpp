#ifndef CAMERA_CONTROLLER_COMPONENT_HPP
#define CAMERA_CONTROLLER_COMPONENT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <map>
#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <application.hpp>
#include <cameraComponent.hpp>
#include <entities/entity.hpp>

using gameTemp::Application;

class CameraControllerComponent : public Component
{
private:
    Application *app;
    CameraComponent *camera;

    float yaw, pitch;
    glm::vec3 position;

    float yaw_sensitivity, pitch_sensitivity, fov_sensitivity;
    glm::vec3 position_sensitivity;
    float speedup_factor = 5.0f; // A speed multiplier if "Left Shift" is held.

    bool mouse_locked = false; //wether the mouse is inside the game window or not

    //CALLED FROM THE READ FUNCTION HERE
    static CameraControllerComponent *CreationFromBase(Entity *camEntity, Application *app)
    {
        CameraControllerComponent *CamController = new CameraControllerComponent(app, camEntity);
        return CamController;
    }

public:
    CameraControllerComponent(Application *application, Entity *myEntity)
    {
        this->app = application;

        int width, height = 0;
        glm::ivec2 wh = app->getFrameBufferSize();
        width = wh.x;
        height = wh.y;

        camera = myEntity->getCameraComponent();
        camera->setupPerspective(glm::pi<float>() / 2, static_cast<float>(width) / height, 0.1f, 100.0f);
        yaw_sensitivity = pitch_sensitivity = 0.01f;
        position_sensitivity = {3.0f, 3.0f, 3.0f};
        fov_sensitivity = glm::pi<float>() / 10;

        position = camera->getEyePosition();
        auto direction = camera->getDirection();
        yaw = glm::atan(-direction.z, direction.x);
        float base_length = glm::sqrt(direction.x * direction.x + direction.z * direction.z);
        pitch = glm::atan(direction.y, base_length);
    }

    int getComponentType()
    {
        return CONTROLLER_COMPONENT;
    }

    void release()
    {
        if (mouse_locked)
        {
            mouse_locked = false;
            app->getMouse().unlockMouse(app->getWindow());
        }
    }

    void update(double delta_time, int recFront, int recBack, int recRight, int recLeft, int recJump, int recCrouch)
    {
        if (app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && !mouse_locked)
        {
            app->getMouse().lockMouse(app->getWindow());
            mouse_locked = true;
        }
        else if (!app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && mouse_locked)
        {
            app->getMouse().unlockMouse(app->getWindow());
            mouse_locked = false;
        }

        if (app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1))
        {
            glm::vec2 delta = app->getMouse().getMouseDelta();
            pitch -= delta.y * pitch_sensitivity;
            yaw -= delta.x * yaw_sensitivity;
        }

        if (pitch < -glm::half_pi<float>() * 0.99f)
            pitch = -glm::half_pi<float>() * 0.99f;
        if (pitch > glm::half_pi<float>() * 0.99f)
            pitch = glm::half_pi<float>() * 0.99f;
        yaw = glm::wrapAngle(yaw);

        float fov = camera->getVerticalFieldOfView() + app->getMouse().getScrollOffset().y * fov_sensitivity;
        fov = glm::clamp(fov, glm::pi<float>() * 0.01f, glm::pi<float>() * 0.99f);
        camera->setVerticalFieldOfView(fov);

        glm::vec3 front = camera->Forward(), up = camera->Up(), right = camera->Right();

        glm::vec3 current_sensitivity = this->position_sensitivity;
        if (app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT))
            current_sensitivity *= speedup_factor;
        if (recFront > 0)
        {
            if (app->getKeyboard().isPressed(recFront))
                position += front * ((float)delta_time * current_sensitivity.z);
        }
        if (recBack > 0)
        {
            if (app->getKeyboard().isPressed(recBack))
                position -= front * ((float)delta_time * current_sensitivity.z);
        }
        if (recJump > 0)
        {
            if (app->getKeyboard().isPressed(recJump))
                position += up * ((float)delta_time * current_sensitivity.y);
        }
        if (recCrouch > 0)
        {
            if (app->getKeyboard().isPressed(recCrouch))
                position -= up * ((float)delta_time * current_sensitivity.y);
        }
        if (recRight > 0)
        {
            if (app->getKeyboard().isPressed(recRight))
                position += right * ((float)delta_time * current_sensitivity.x);
        }
        if (recLeft > 0)
        {
            if (app->getKeyboard().isPressed(recLeft))
                position -= right * ((float)delta_time * current_sensitivity.x);
        }

        camera->setDirection(glm::vec3(glm::cos(yaw), 0, -glm::sin(yaw)) * glm::cos(pitch) + glm::vec3(0, glm::sin(pitch), 0));
        camera->setEyePosition(position);
    }

    [[nodiscard]] float getYaw() const { return yaw; }
    [[nodiscard]] float getPitch() const { return pitch; }
    [[nodiscard]] glm::vec3 getPosition() const { return position; }

    [[nodiscard]] float getYawSensitivity() const { return yaw_sensitivity; }
    [[nodiscard]] float getPitchSensitivity() const { return pitch_sensitivity; }
    [[nodiscard]] float getFieldOfViewSensitivity() const { return fov_sensitivity; }
    [[nodiscard]] glm::vec3 getPositionSensitivity() const { return position_sensitivity; }
    [[nodiscard]] float getSpeedUpFactor() const { return speedup_factor; }

    void setYaw(float _yaw)
    {
        this->yaw = glm::wrapAngle(_yaw);
    }

    void setPitch(float _pitch)
    {
        const float v = 0.99f * glm::pi<float>() / 2;
        if (_pitch > v)
            _pitch = v;
        else if (_pitch < -v)
            _pitch = -v;
        this->pitch = _pitch;
    }

    void setPosition(glm::vec3 _pos)
    {
        this->position = _pos;
    }

    void setYawSensitivity(float sensitivity) { this->yaw_sensitivity = sensitivity; }
    void setPitchSensitivity(float sensitivity) { this->pitch_sensitivity = sensitivity; }
    void setFieldOfViewSensitivity(float sensitivity) { this->fov_sensitivity = sensitivity; }
    void setPositionSensitivity(glm::vec3 sensitivity) { this->position_sensitivity = sensitivity; }
    //Map of the keyboard with key=keyName and value of glfw key number
    static void GenerateKeyboardMap(map<string, int> &keyboardMap)
    {
        string textFilePath = "./assets/files/keyboard.txt";
        string line;
        ifstream myfile(textFilePath);
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                int index;
                char *cstr = const_cast<char *>(line.c_str());
                for (int i = 0; i < line.size(); i++)
                {
                    if (cstr[i] == ' ')
                    {
                        index = i;
                        break;
                    }
                }
                string first = line.substr(0, index);
                string second = line.substr(index + 1, line.size());
                keyboardMap[first] = (stoi(second));
            }
            myfile.close();
        }
    }
    //Read Data
    static void ReadData(string path, vector<Entity *> entities, vector<CameraControllerComponent *> &camControllerVector, Application *app, vector<int> &entitesPos, vector<map<string, int>> &CameraControllerComponentControllers)
    {
        map<string, int> keyboardControls;
        GenerateKeyboardMap(keyboardControls);
        Json::Value data;
        std::ifstream people_file(path, std::ifstream::binary);
        people_file >> data;
        int numOfCamController = data["World"]["Camera Controllers"]["Array"].size();
        //cout << "INSIDEEEEE THE CAMERAAAA CONTROLLLLLERRRRRR " << numOfCamController << endl;
        //Temp vector of each camera controller keys
        map<string, int> tempMap;
        tempMap["front"] = -1;
        tempMap["back"] = -1;
        tempMap["right"] = -1;
        tempMap["left"] = -1;
        tempMap["jump"] = -1;
        tempMap["crouch"] = -1;
        vector<map<string, int>> CameraControllerComponentControllersTemp(numOfCamController, tempMap);
        //
        int numOfEntityToControl;
        string upString;
        string downString;
        string rightString;
        string leftString;
        string jumpString;
        string crouchString;
        for (int i = 0; i < numOfCamController; i++)
        {
            numOfEntityToControl = data["World"]["Camera Controllers"]["Array"][i]["Number of Entity to Control"].asInt();
            upString = data["World"]["Camera Controllers"]["Array"][i]["Keys"]["Front"].asString();
            downString = data["World"]["Camera Controllers"]["Array"][i]["Keys"]["Back"].asString();
            rightString = data["World"]["Camera Controllers"]["Array"][i]["Keys"]["Right"].asString();
            leftString = data["World"]["Camera Controllers"]["Array"][i]["Keys"]["Left"].asString();
            jumpString = data["World"]["Camera Controllers"]["Array"][i]["Keys"]["Jump"].asString();
            crouchString = data["World"]["Camera Controllers"]["Array"][i]["Keys"]["Crouch"].asString();
            // retrieve the glfwNumbers for the fetched key names and place it in the map of keys
            CameraControllerComponentControllersTemp[i]["front"] = keyboardControls[upString];
            CameraControllerComponentControllersTemp[i]["back"] = keyboardControls[downString];
            CameraControllerComponentControllersTemp[i]["right"] = keyboardControls[rightString];
            CameraControllerComponentControllersTemp[i]["left"] = keyboardControls[leftString];
            CameraControllerComponentControllersTemp[i]["jump"] = keyboardControls[jumpString];
            CameraControllerComponentControllersTemp[i]["crouch"] = keyboardControls[crouchString];
            //
            /*cout << upString << downString << rightString << leftString << jumpString << crouchString << endl
                 << endl;

            cout << endl
                 << endl;
            cout << "Numer of entity to control" << numOfEntityToControl << endl;

            cout << endl
                 << "The entitttttty is " << entities[numOfEntityToControl - 1] << endl;*/
            //
            entitesPos.push_back(numOfEntityToControl - 1); //Where is position of the camera controller entity
            camControllerVector.push_back(CreationFromBase(entities[numOfEntityToControl - 1], app));
            //cout << "WESEEEEEELLLT L HENNAAAAAA     " << numOfEntityToControl << endl;
            CameraControllerComponentControllers = CameraControllerComponentControllersTemp; // map for each camera controller component of the glfw key numbers
            /*cout << "HEREEEEEEEEEEEEEEEEEEEEE" << endl
                 << endl
                 << endl;
            cout << CameraControllerComponentControllers[i]["front"] << endl;
            cout << CameraControllerComponentControllers[i]["back"] << endl;
            cout << CameraControllerComponentControllers[i]["right"] << endl;
            cout << CameraControllerComponentControllers[i]["left"] << endl;
            cout << CameraControllerComponentControllers[i]["jump"] << endl;
            cout << CameraControllerComponentControllers[i]["crouch"] << endl;*/
            /* cout << endl
                 << "THE INDEX ISSSSSSSSSSSSSS  " << i << endl;*/
        }
    }
};

#endif