#ifndef MOVEMENT_CONTROLLER_HPP
#define MOVEMENT_CONTROLLER_HPP

#include <application.hpp>
#include <glm/glm.hpp>
#include <component.hpp>
#include <vector>
#include <map>

using gameTemp::Application;
using std::map;
using std::vector;

enum Animation
{
    KEYS,
    ROTATION
};

class MovementControllerComponenet : public Component
{
private:
    bool enabled = true;
    Application *app;
    glm::vec3 position_sensitivity = {70.0f, 70.0f, 70.0f};
    float speedup_factor = 5.0f;
    vector<Animation> animations;
    map<string, int> controllerKeys;

    void updateBouncingMotion(double deltaTime);
    void updateControllerMotion(double deltaTime);
    void updateRotationMotion(double deltaTime);

public:
    MovementControllerComponenet(Application *app);
    void setControllerKeys(map<string, int> &keysMap);
    int getComponentType();
    void addAnimation(Animation newAnimation);
    void update(double deltaTime);
    ~MovementControllerComponenet();
};

#endif