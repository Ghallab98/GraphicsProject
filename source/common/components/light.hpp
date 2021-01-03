//
// Created by Karim on 1/3/2021.
//

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.inl>


class Light : public Component {
private:
    LightType type;
    bool enabled;
    glm::vec3 color{};
    glm::vec3 position{}; // Used for Point and Spot Lights only
    glm::vec3 direction{}; // Used for Directional and Spot Lights only
    Attenuation attenuation{};
    spotAngle spot_angle{};


public:
    Light(LightType type,bool enabled, glm::vec3 color, Attenuation attenuation,spotAngle spot_angle);
    void setType(LightType type);
    void setPosition( glm::vec3 position);
    void setDirection( glm::vec3 direction);
    void enable() {
        this->enabled = true;
    }
    void disable() {
        this->enabled=false;
    }
    void setAttenuation(Attenuation a);
    void setSpotAngle(spotAngle s);
    LightType getType() const;
    bool isEnabled() const;
    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;
    Attenuation getAttenuation() const;
    spotAngle getSpotAngle() const;
    ~Light();



};


#endif //GFX_LAB_LIGHT_HPP
