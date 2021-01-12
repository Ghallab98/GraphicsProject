//
// Created by Karim on 1/3/2021.
//

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <component.hpp>
#include <glm/glm.hpp>
#include "../materialClass/material.hpp"
#include "../shader.hpp"

enum class LightType
{
    DIRECTIONAL,
    POINT,
    SPOT
};

struct Attenuation
{
    float constant, linear, quadratic;
};

struct SpotAngle
{
    float inner, outer;
};

class Light : public Component
{
private:
    LightType type;
    bool enabled;
    glm::vec3 color;
    glm::vec3 position;  // TODO:Used for Point and Spot Lights only
    glm::vec3 direction; // Used for Directional and Spot Lights only
    Attenuation attenuation;
    SpotAngle spot_angle;

public:
    Light(LightType type, bool enabled, glm::vec3 color, Attenuation attenuation, SpotAngle spot_angle);

    void setType(LightType type);
    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);
    void setAttenuation(Attenuation a);
    void setSpotAngle(SpotAngle s);

    bool isEnabled() const;
    void enable();
    void disable();

    int getComponentType();
    LightType getType() const;
    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;
    Attenuation getAttenuation() const;
    SpotAngle getSpotAngle() const;
    //
    Light *CreationFromBase();

    ~Light();
};

#endif //GFX_LAB_LIGHT_HPP
