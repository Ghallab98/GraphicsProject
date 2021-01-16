#include "light.hpp"

LightComponent::LightComponent(LightType type = LightType::DIRECTIONAL)
{
    this->type = type;
}

void LightComponent::setType(LightType type)
{
    this->type = type;
}

void LightComponent::setDirection(glm::vec3 direction)
{
    this->direction = direction;
}

void LightComponent::setPosition(glm::vec3 position)
{
    this->position = position;
}

void LightComponent::setSpotAngle(SpotAngle s)
{
    this->spot_angle.inner = s.inner;
    this->spot_angle.outer = s.outer;
}

void LightComponent::setAttenuation(Attenuation a)
{
    this->attenuation.constant = a.constant;
    this->attenuation.linear = a.linear;
    this->attenuation.quadratic = a.quadratic;
}

LightType LightComponent::getType() const
{
    return this->type;
}

void LightComponent::setColor(glm::vec3 color)
{
    this->color = color;
}

glm::vec3 LightComponent::getPosition() const
{
    return this->position;
}

glm::vec3 LightComponent::getColor() const
{
    return this->color;
}

glm::vec3 LightComponent::getDirection() const
{
    return this->direction;
}

Attenuation LightComponent::getAttenuation() const
{
    return this->attenuation;
}

SpotAngle LightComponent::getSpotAngle() const
{
    return this->spot_angle;
}

bool LightComponent::isEnabled() const
{
    return this->enabled;
}

void LightComponent::enable()
{
    this->enabled = true;
}

void LightComponent::disable()
{
    this->enabled = false;
}

int LightComponent::getComponentType()
{
    return LIGHT_COMPONENT;
}

LightComponent::~LightComponent() {}

void LightComponent::configureShader(int light_index, glm::mat4 cameraMatrix, ShaderProgram *program)
{
    if (!enabled)
        return;

    program->set("light_count", light_index + 1);
    std::string prefix;
    switch (type)
    {
    case LightType::SKYLIGHT:
        program->set("sky_light.top_color", this->top_color);
        program->set("sky_light.middle_color", this->middle_color);
        program->set("sky_light.bottom_color", this->bottom_color);
        break;
    case LightType::DIRECTIONAL:
        prefix = "lights[" + std::to_string(light_index) + "].";
        program->set(prefix + "type", static_cast<int>(this->type));
        program->set(prefix + "color", this->color);
        program->set(prefix + "direction", glm::normalize(this->direction));
        break;
    case LightType::POINT:
        prefix = "lights[" + std::to_string(light_index) + "].";
        program->set(prefix + "type", static_cast<int>(this->type));
        program->set(prefix + "color", this->color);
        program->set(prefix + "position", this->position);
        program->set(prefix + "attenuation_constant", this->attenuation.constant);
        program->set(prefix + "attenuation_linear", this->attenuation.linear);
        program->set(prefix + "attenuation_quadratic", this->attenuation.quadratic);
        break;
    case LightType::SPOT:
        prefix = "lights[" + std::to_string(light_index) + "].";
        program->set(prefix + "type", static_cast<int>(this->type));
        program->set(prefix + "color", this->color);
        program->set(prefix + "position", this->position);
        program->set(prefix + "direction", glm::normalize(this->direction));
        program->set(prefix + "attenuation_constant", this->attenuation.constant);
        program->set(prefix + "attenuation_linear", this->attenuation.linear);
        program->set(prefix + "attenuation_quadratic", this->attenuation.quadratic);
        program->set(prefix + "inner_angle", this->spot_angle.inner);
        program->set(prefix + "outer_angle", this->spot_angle.outer);
        break;
    }
}

// LightComponent *LightComponent::CreationFromBase()
// {
// }
