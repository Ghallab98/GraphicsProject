#include "movemenetController.hpp"

#define PI 3.1415926535897932384626433832795

MovementControllerComponenet::MovementControllerComponenet(Application *app)
{
    this->app = app;
}

int MovementControllerComponenet::getComponentType()
{
    return MOVEMENT_CONTROLLER_COMPONENT;
}

void MovementControllerComponenet::addAnimation(Animation newAnimation)
{
    this->animations.push_back(newAnimation);
    std::sort(std::begin(animations), std::end(animations));
}

void MovementControllerComponenet::setControllerKeys(map<string, int> &keysMap)
{
    this->controllerKeys = keysMap;
}

void MovementControllerComponenet::setMovementLimits(MovemenetLimits limits)
{
    myLimits = limits;
}

void MovementControllerComponenet::update(double deltaTime)
{
    for (int i = 0, numAnimations = animations.size(); i < numAnimations; i++)
    {
        switch (animations[i])
        {
        case KEYS:
            updateControllerMotion(deltaTime);
            break;
        case ROTATION:
            updateRotationMotion(deltaTime);
            break;
        default:
            break;
        }
    }
}

void MovementControllerComponenet::updateControllerMotion(double deltaTime)
{
    // Speedup movement
    glm::vec3 current_sensitivity = this->position_sensitivity;
    if (app->getKeyboard().isPressed(controllerKeys["speedUp"]))
        current_sensitivity *= speedup_factor;

    // Move entity
    glm::vec3 translation = {0.0f, 0.0f, 0.0f};
    glm::vec3 myPosition = myEntity->getTransformationComponent()->getTranslation();

    if (app->getKeyboard().isPressed(controllerKeys["forward"]) &&
        (myPosition.z + (float)deltaTime * current_sensitivity.z) < myLimits.z_end)
    {
        translation = {translation.x, translation.y, translation.z + (float)deltaTime * current_sensitivity.z};
    }

    if (app->getKeyboard().isPressed(controllerKeys["backward"]) &&
        (myPosition.z - (float)deltaTime * current_sensitivity.z) > myLimits.z_start)
    {
        translation = {translation.x, translation.y, translation.z - (float)deltaTime * current_sensitivity.z};
    }

    if (app->getKeyboard().isPressed(controllerKeys["up"]) &&
        (myPosition.y + (float)deltaTime * current_sensitivity.y) < myLimits.y_end)
    {
        translation = {translation.x, translation.y + (float)deltaTime * current_sensitivity.y, translation.z};
    }

    if (app->getKeyboard().isPressed(controllerKeys["down"]) &&
        (myPosition.y - (float)deltaTime * current_sensitivity.y) > myLimits.y_start)
    {
        translation = {translation.x, translation.y - (float)deltaTime * current_sensitivity.y, translation.z};
    }

    if (app->getKeyboard().isPressed(controllerKeys["right"]) &&
        (myPosition.x + (float)deltaTime * current_sensitivity.x) < myLimits.x_end)
    {
        translation = {translation.x + (float)deltaTime * current_sensitivity.x, translation.y, translation.z};
    }

    if (app->getKeyboard().isPressed(controllerKeys["left"]) &&
        (myPosition.x - (float)deltaTime * current_sensitivity.x) > myLimits.x_start)
    {
        translation = {translation.x - (float)deltaTime * current_sensitivity.x, translation.y, translation.z};
    }

    myEntity->getTransformationComponent()->transform(translation);
}

void MovementControllerComponenet::updateRotationMotion(double deltaTime)
{
    glm::vec3 rotation = {0.0f, 0.1 * glm::sin(2 * PI * deltaTime), 0.0f};
    myEntity->getTransformationComponent()->transform({0, 0, 0}, rotation);
}

MovementControllerComponenet::~MovementControllerComponenet() {}