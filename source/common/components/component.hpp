#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <json/value.h>
#include <json/json.h>
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
    static void ReadData(std::string inputFilepath, int &numOfEntites, vector<TransformationComponent *> &tcVectors) // to be called from the Game.cpp
    {
        numOfEntites = 5;
        cout << "Invoked" << endl
             << endl
             << endl;

        //TransformationComponent *tc ;
        TransformationComponent::CreationFromBase(nullptr, (1, 2, 3), (2, 3, 4), (4, 5, 6));
        //Json::Value data;
        std::ifstream people_file(inputFilepath, std::ifstream::binary);
        //people_file >> data;

        //cout << people; //This will print the entire json object.

        //The following lines will let you access the indexed objects.
        //cout << people["entity1"]["Transformation Component"]["position"][0]; //Prints the value for "Anna"
    }
};

#endif