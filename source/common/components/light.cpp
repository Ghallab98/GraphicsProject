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
//Sky light setters
void LightComponent::setSkyTopClr(glm::vec3 myTopClr)
{
    this->top_color = myTopClr;
}
void LightComponent::setSkyMidClr(glm::vec3 mymidClr)
{
    this->middle_color = mymidClr;
}
void LightComponent::setSkyBtmClr(glm::vec3 mybtmClr)
{
    this->bottom_color = mybtmClr;
}
//Creation from base
LightComponent *LightComponent::CreationSkyFromBase(glm::vec3 topColor, glm::vec3 middleColor, glm::vec3 bottomColor)
{
    LightComponent *skyLigthComp = new LightComponent(LightType::SKYLIGHT);
    skyLigthComp->setSkyTopClr(topColor);
    skyLigthComp->setSkyMidClr(middleColor);
    skyLigthComp->setSkyBtmClr(bottomColor);
    return skyLigthComp;
}
LightComponent *LightComponent::CreationSpotFromBase(glm::vec3 colorVec, glm::vec3 posVec, glm::vec3 dirVec, glm::vec3 attnVec, glm::vec2 spotVec)
{
    LightComponent *spotLigthComp = new LightComponent(LightType::SPOT);
    spotLigthComp->setColor(colorVec);
    spotLigthComp->setPosition(posVec);
    spotLigthComp->setDirection(dirVec);
    Attenuation tobesentAtt;
    tobesentAtt.constant = attnVec[0]; //free term
    tobesentAtt.linear = attnVec[1];   //linear
    tobesentAtt.quadratic = attnVec[2];
    spotLigthComp->setAttenuation(tobesentAtt);
    SpotAngle s1;
    s1.inner = spotVec[0];
    s1.outer = spotVec[1];
    spotLigthComp->setSpotAngle(s1);
    return spotLigthComp;
}
LightComponent *LightComponent::CreationDirectionalFromBase(glm::vec3 direction, glm::vec3 color)
{
    LightComponent *dirLightComp = new LightComponent(LightType::DIRECTIONAL);
    dirLightComp->setColor(color);
    dirLightComp->setDirection(direction);
    return dirLightComp;
}
LightComponent *LightComponent::CreationPointFromBase(glm::vec3 clrVec, glm::vec3 posVec, glm::vec3 attnVec)
{
    LightComponent *pointLightComp = new LightComponent(LightType::POINT);
    pointLightComp->setColor(clrVec);
    pointLightComp->setPosition(posVec);
    Attenuation tobesentAtt;
    tobesentAtt.constant = attnVec[0]; //free term
    tobesentAtt.linear = attnVec[1];   //linear
    tobesentAtt.quadratic = attnVec[2];
    pointLightComp->setAttenuation(tobesentAtt);
    return pointLightComp;
}
//ReadData
void LightComponent::ReadData(string filePath, int numOfEntities, vector<LightComponent *> &lightVec, vector<bool> &isEntityLight)
{
    Json::Value data;
    std::ifstream people_file(filePath, std::ifstream::binary);
    people_file >> data;
    string entity = "entity";
    string entityTemp = "entity";
    for (int pos = 1; pos <= numOfEntities; pos++)
    {
        entity += to_string(pos);
        bool isLight = data["World"][entity]["light"].asBool();
        if (isLight)
        {
            if (data["World"][entity]["Light Component"])
            {
                string lightType = data["World"][entity]["Light Component"]["type"].asString();
                if (lightType == "sky")
                {
                    float topClr[3] = {0.0, 0.0, 0.0};
                    float midClr[3] = {0.0, 0.0, 0.0};
                    float btClr[3] = {0.0, 0.0, 0.0};
                    for (int i = 0; i < 3; i++)
                    {
                        topClr[i] = data["World"][entity]["Light Component"]["top-color"][i].asFloat();
                        midClr[i] = data["World"][entity]["Light Component"]["middle-color"][i].asFloat();
                        btClr[i] = data["World"][entity]["Light Component"]["bottom-color"][i].asFloat();
                    }
                    glm::vec3 topClrVec = {topClr[0], topClr[1], topClr[2]};
                    glm::vec3 midClrVec = {midClr[0], midClr[1], midClr[2]};
                    glm::vec3 btClrVec = {btClr[0], btClr[1], btClr[2]};
                    /*cout << "I am the sky light  " << endl;
                    cout << topClrVec[0] << topClrVec[1] << topClrVec[2] << endl;
                    cout << midClrVec[0] << midClrVec[1] << midClrVec[2] << endl;
                    cout << btClrVec[0] << btClrVec[1] << btClrVec[2] << endl;*/
                    lightVec.push_back(CreationSkyFromBase(topClrVec, midClrVec, btClrVec));
                }
                else if (lightType == "spot")
                {
                    float color[3] = {1.0, 1.0, 1.0};
                    float direction[3] = {-1, -1, -1};
                    float position[3] = {0, 1, 5};
                    float attenuation[3] = {0.0, 0.0, 1.0};
                    float spot[2] = {0.0, 0.3};
                    for (int i = 0; i < 3; i++)
                    {
                        direction[i] = data["World"][entity]["Light Component"]["direction"][i].asFloat();
                        position[i] = data["World"][entity]["Light Component"]["position"][i].asFloat();
                        color[i] = data["World"][entity]["Light Component"]["color"][i].asFloat();
                        attenuation[i] = data["World"][entity]["Light Component"]["Attenuation"][i].asFloat();
                        if (i < 2)
                            spot[i] = data["World"][entity]["Light Component"]["spot"][i].asFloat();
                    }
                    glm ::vec3 clrVec = {color[0], color[1], color[2]};
                    glm ::vec3 posVec = {position[0], position[1], position[2]};
                    glm ::vec3 dirVec = {direction[0], direction[1], direction[2]};
                    glm ::vec3 attnVec = {attenuation[0], attenuation[1], attenuation[2]};
                    glm ::vec2 spotVec = {spot[0], spot[1]};
                    lightVec.push_back(CreationSpotFromBase(clrVec, posVec, dirVec, attnVec, spotVec));
                }
                else if (lightType == "directional")
                {
                    float color[3] = {1.0, 1.0, 1.0};
                    float direction[3] = {-1, -1, -1};
                    for (int i = 0; i < 3; i++)
                    {
                        direction[i] = data["World"][entity]["Light Component"]["direction"][i].asFloat();
                        color[i] = data["World"][entity]["Light Component"]["color"][i].asFloat();
                    }
                    glm::vec3 clrVec = {color[0], color[1], color[2]};
                    glm::vec3 dirVec = {direction[0], direction[1], direction[2]};
                    /* cout << "I am  the directional light  " << endl;
                    cout << clrVec[0] << clrVec[1] << clrVec[2] << endl;
                    cout << dirVec[0] << dirVec[1] << dirVec[2] << endl;*/
                    lightVec.push_back(CreationDirectionalFromBase(dirVec, clrVec));
                }
                else if (lightType == "point")
                {
                    float color[3] = {1.0, 1.0, 1.0};
                    float position[3] = {0, 1, 5};
                    float attenuation[3] = {0.0, 0.0, 1.0};
                    for (int i = 0; i < 3; i++)
                    {
                        position[i] = data["World"][entity]["Light Component"]["position"][i].asFloat();
                        color[i] = data["World"][entity]["Light Component"]["color"][i].asFloat();
                        attenuation[i] = data["World"][entity]["Light Component"]["Attenuation"][i].asFloat();
                    }
                    glm::vec3 clrVec = {color[0], color[1], color[2]};
                    glm::vec3 posVec = {position[0], position[1], position[2]};
                    glm::vec3 attnVec = {attenuation[0], attenuation[1], attenuation[2]};
                    /*cout << "I am the point  " << endl;
                    cout << clrVec[0] << clrVec[1] << clrVec[2] << endl;
                    cout << posVec[0] << posVec[1] << posVec[2] << endl;
                    cout << attnVec[0] << attnVec[1] << attnVec[2] << endl;*/
                    lightVec.push_back(CreationPointFromBase(clrVec, posVec, attnVec));
                }
                isEntityLight.push_back(true);
            }
        }
        else
        {
            isEntityLight.push_back(false);
            lightVec.push_back(nullptr);
        }
        //last line
        entity = entityTemp;
    }
}
