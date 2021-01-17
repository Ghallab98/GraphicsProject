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
    SPOT,
    SKYLIGHT
};

struct Attenuation
{
    float constant, linear, quadratic;
};

struct SpotAngle
{
    float inner;
    float outer;
};

class LightComponent : public Component
{
private:
    LightType type;
    bool enabled = true;
    //sky
    glm::vec3 top_color = {0.25f, 0.3f, 0.5f};
    glm::vec3 middle_color = {0.35f, 0.35f, 0.4f};
    glm::vec3 bottom_color = {0.25f, 0.25f, 0.25f};
    //
    glm::vec3 color = {1.0f, 1.0f, 1.0f};
    glm::vec3 position = {0, 1, 5};
    glm::vec3 direction = {-1, -1, -1};
    Attenuation attenuation = {0.0f, 0.0f, 1.0f};
    SpotAngle spot_angle = {glm::quarter_pi<float>(), glm::half_pi<float>()};
    //private fn
    static LightComponent *CreationSkyFromBase(glm::vec3 topColor, glm::vec3 middleColor, glm::vec3 bottomColor);
    static LightComponent *CreationSpotFromBase(glm::vec3 colorVec, glm::vec3 posVec, glm::vec3 dirVec, glm::vec3 attnvec, glm::vec2 spotVec);
    static LightComponent *CreationDirectionalFromBase(glm::vec3 direction, glm::vec3 color);
    static LightComponent *CreationPointFromBase(glm::vec3 clrVec, glm::vec3 posVec, glm::vec3 attnVec);

public:
    LightComponent(LightType type);

    void setType(LightType type);
    //
    void setColor(glm::vec3 color);
    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);
    //
    void setAttenuation(Attenuation a);
    void setSpotAngle(SpotAngle s);
    //
    void setSkyTopClr(glm::vec3 myTopClr);
    void setSkyMidClr(glm::vec3 mymidClr);
    void setSkyBtmClr(glm::vec3 mybtmClr);
    //
    bool isEnabled() const;
    void enable();
    void disable();

    int getComponentType();
    LightType getType() const;
    glm::vec3 getColor() const;
    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;
    Attenuation getAttenuation() const;
    SpotAngle getSpotAngle() const;

    void configureShader(int light_index, glm::mat4 cameraMatrix, ShaderProgram *program);

    //
    static void ReadData(string filePath, int numOfEntities, vector<LightComponent *> &lightVec, vector<bool> &isEntityLight, int &skyLightIndexInEntitiesVec);

    ~LightComponent();
};

#endif //GFX_LAB_LIGHT_HPP
