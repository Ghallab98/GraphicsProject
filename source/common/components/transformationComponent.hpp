#ifndef TRANSFORMATION_COMPONENT_HPP
#define TRANSFORMATION_COMPONENT_HPP

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <iostream>
#include "../../vendor/jsoncpp/include/json/value.h"
#include "../../vendor/jsoncpp/include/json/json.h"
#include <fstream>
#include <string.h>
#include <vector>

#include <component.hpp>

class Component;
class TransformationComponent;
class CameraComponent;
class CameraControllerComponent;
class MeshRenderer;
class Light;

class TransformationComponent : public Component
{
private:
    std::vector<TransformationComponent *> children;
    glm::mat4 transformationMatrix;
    glm::vec3 position;
    //TO BE CALLED FROM READ FILE IN THIS CLASS
    static TransformationComponent *CreationFromBase(TransformationComponent *parent, glm::vec3 translation, glm ::vec3 rotation, glm::vec3 scaling)
    {
        TransformationComponent *TC_Comp = new TransformationComponent(parent);
        TC_Comp->transform(translation, rotation, scaling);
        return TC_Comp;
    }

public:
    TransformationComponent(TransformationComponent *parent)
    {
        if (parent)
        {
            parent->children.push_back(this);
            this->transformationMatrix = parent->transformationMatrix;
        }
        else
            transformationMatrix = glm::mat4(1.0f);
    }

    int getComponentType()
    {
        return TRANSFORMATION_COMPONENT;
    }

    bool hasChildren()
    {
        return children.size() != 0;
    }

    void transform(const glm::vec3 &translation = {0, 0, 0},
                   const glm::vec3 &rotation = {0, 0, 0},
                   const glm::vec3 &scale = {1, 1, 1})
    {
        glm::mat4 transformationMatrix = calculateTransformationMatrix(translation, rotation, scale);
        transformChildren(this, transformationMatrix);
    }

    void transformChildren(TransformationComponent *parent, glm::mat4 &transformationMatrix)
    {
        parent->transformationMatrix *= transformationMatrix;

        for (int i = 0, numChild = parent->children.size(); i < numChild; i++)
            transformChildren(parent->children[i], transformationMatrix);
    }

    const glm::mat4 getTransformationMatrix()
    {
        return transformationMatrix;
    }

    static glm::mat4 calculateTransformationMatrix(
        const glm::vec3 &translation = {0, 0, 0},
        const glm::vec3 &rotation = {0, 0, 0},
        const glm::vec3 &scale = {1, 1, 1})
    {
        return glm::translate(glm::mat4(1.0f), translation) *
               glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
               glm::scale(glm::mat4(1.0f), scale);
    }
    ///
    static void ReadData(string inputFile, int numOfEntities, vector<TransformationComponent *> &tcVector)
    {
        Json::Value data;
        std::ifstream people_file(inputFile, std::ifstream::binary);
        people_file >> data;
        string entity = "entity";
        string entityTemp = "entity";
        for (int num = 1; num <= numOfEntities; num++)
        {
            entity += to_string(num);
            int parntEntityNum = data["World"][entity]["entityParentNum"].asInt() - 1;
            //-- Translation
            int posVal[3];
            int posIndex;
            for (int j = 0; j < 3; j++)
            {
                posIndex = (data["World"][entity]["Transformation Component"]["position"][j]).asInt();
                posVal[j] = posIndex;
            }
            glm::vec3 translation(posVal[0], posVal[1], posVal[2]);
            //cout << "Translation is " << posVal[0] << posVal[1] << posVal[2] << endl;
            //-- Rotation
            int rotIndex;
            int rotVal[3];
            for (int j = 0; j < 3; j++)
            {
                rotIndex = (data["World"][entity]["Transformation Component"]["rotation"][j]).asInt();
                rotVal[j] = rotIndex;
            }
            glm::vec3 rotation(rotVal[0], rotVal[1], rotVal[2]);
            //cout << "Rotation is " << rotVal[0] << rotVal[1] << rotVal[2] << endl;
            //-- Scaling
            int scaleIndex;
            int scaleVal[3];
            for (int j = 0; j < 3; j++)
            {
                scaleIndex = (data["World"][entity]["Transformation Component"]["scale"][j]).asInt();
                scaleVal[j] = scaleIndex;
            }
            glm::vec3 scale(scaleVal[0], scaleVal[1], scaleVal[2]);
            //cout << "Scaling is " << scaleVal[0] << scaleVal[1] << scaleVal[2] << endl;
            //Creation of TC
            if (parntEntityNum <= -1)
            {
                tcVector.push_back(CreationFromBase(nullptr, translation, rotation, scale));
            }
            else
            {
                tcVector.push_back(CreationFromBase(tcVector[parntEntityNum], translation, rotation, scale));
            }
            //last line in the for loop
            entity = entityTemp;
        }
    }
};

#endif