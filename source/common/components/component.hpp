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

class Entity;
class TransformationComponent;

class Component
{
protected:
    Entity *myEntity;

public:
    Component() {}
    virtual ~Component() {}
    virtual int getComponentType() = 0;

    void setEntity(Entity *entity)
    {
        myEntity = entity;
    }
    //
    static void ReadData(std::string inputFilepath, int &numOfEntites) // to be called from the Game.cpp
    {

        Json::Value data;
        std::ifstream people_file(inputFilepath, std::ifstream::binary);
        people_file >> data;
        numOfEntites = data["NumberOfEntities"].asInt();
    }
};

#endif