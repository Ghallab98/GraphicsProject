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
    ROTATION,
    KEYS
};

struct MovemenetLimits
{
    float x_start = -100;
    float x_end = 100;
    float y_start = -100;
    float y_end = 100;
    float z_start = -100;
    float z_end = 100;
};

class MovementControllerComponenet : public Component
{
private:
    bool enabled = true;
    Application *app;
    glm::vec3 position_sensitivity = {3.0f, 3.0f, 3.0f};
    float speedup_factor = 5.0f;
    vector<Animation> animations;
    map<string, int> controllerKeys;
    MovemenetLimits myLimits;

    void updateBouncingMotion(double deltaTime);
    void updateControllerMotion(double deltaTime);
    void updateRotationMotion(double deltaTime);

public:
    MovementControllerComponenet(Application *app);
    void setControllerKeys(map<string, int> &keysMap);
    void setMovementLimits(MovemenetLimits limits);
    int getComponentType();
    void addAnimation(Animation newAnimation);
    void update(double deltaTime);
    ~MovementControllerComponenet();
};

#endif