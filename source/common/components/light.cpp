//
// Created by Karim on 1/3/2021.
//

#include "light.hpp"

Light::Light(LightType type, bool enabled = true, glm::vec3 color = {1, 1, 1},
             Attenuation attenuation = {0.0f, 0.0f, 1.0f},
             spotAngle spot_angle = {glm::quarter_pi<float>(), glm::half_pi<float>()})
{
    this->type = type;
    this->enabled = enabled;
    this->color = color;
    this->attenuation = attenuation;
    this->spot_angle = spot_angle;
}

void Light::setType(LightType type)
{
    this->type = type;
}

void Light::setDirection(glm::vec3 direction)
{
    this->direction = direction;
}

void Light::setPosition(glm::vec3 position)
{
    this->position = position;
}

void Light::setSpotAngle(SpotAngle s = {glm::quarter_pi<float>(), glm::half_pi<float>()})
{
    this->spot_angle.inner = s.inner;
    this->spot_angle.outer = s.outer;
}

void Light::setAttenuation(Attenuation a = {0.0f, 0.0f, 1.0f})
{
    this->attenuation.constant = a.constant;
    this->attenuation.linear = a.linear;
    this->attenuation.quadratic = a.quadratic;
}

LightType Light::getType() const
{
    return this->type;
}

glm::vec3 Light::getPosition() const
{
    return this->position;
}

glm::vec3 Light::getDirection() const
{
    return this->direction;
}

Attenuation Light::getAttenuation() const
{
    return this->attenuation;
}

SpotAngle Light::getSpotAngle() const
{
    return this->spot_angle;
}

bool Light::isEnabled() const
{
    return this->enabled;
}

void Light::enable()
{
    this->enabled = true;
}

void Light::disable()
{
    this->enabled = false;
}

int Light::getComponentType()
{
    return LIGHT_COMPONENT;
}
//
Light *Light::CreationFromBase()
{
}
