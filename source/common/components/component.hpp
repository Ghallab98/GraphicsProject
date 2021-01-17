#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include "../../vendor/jsoncpp/include/json/value.h"
#include "../../vendor/jsoncpp/include/json/json.h"
#include <fstream>
#include <string.h>
#include <vector>
//#include "transformationComponent.hpp"
using namespace std;
//
#define TRANSFORMATION_COMPONENT 0
#define CAMERA_COMPONENT 1
#define CONTROLLER_COMPONENT 2
#define MESH_RENDERER_COMPONENT 3
#define LIGHT_COMPONENT 4
#define MOVEMENT_CONTROLLER_COMPONENT 5

class Entity;
class TransformationComponent;

class Component
{
protected:
    Entity *myEntity = nullptr;

public:
    Component() {}
    virtual ~Component() {}
    virtual int getComponentType() = 0;

    void setEntity(Entity *entity)
    {
        myEntity = entity;
    }
    //
    static void ReadData(std::string inputFilepath, int &numOfEntites, int &numOfCamEntities, int &numOfCamController, int &numOfLights) // to be called from the Game.cpp
    {

        Json::Value data;
        std::ifstream people_file(inputFilepath, std::ifstream::binary);
        people_file >> data;
        numOfEntites = data["World"]["NumberOfEntities"].asInt();
        numOfCamEntities = data["World"]["NumberOfCameraEntities"].asInt();
        numOfCamController = data["World"]["Camera Controllers"]["Array"].size();
        numOfLights = data["World"]["NumberOfLightEntities"].asInt();
    }
};

#endif