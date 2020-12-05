#ifndef TRANSFORMATION_COMPONENT_HPP
#define TRANSFORMATION_COMPONENT_HPP

#include<glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <vector>
#include <iostream>
#include "./component.hpp"
using namespace std;

class TransformationComponent : public Component
{
private:
    std::vector<TransformationComponent *> children;
    glm::mat4 transfomrationMatrix;

public:
    TransformationComponent(TransformationComponent *parent)
    {
        if (parent)
        {
            parent->children.push_back(this);
            this->setTransformationMatrix( parent->transfomrationMatrix);
        }
        else
            transfomrationMatrix = glm::mat4(1.0f);
    }

//    bool hasChildren()
//    {
//        return (children.size() == 0);
//    }
    bool hasChildren()
    {
        if (this->children.size() > 0)
            return true;
        else
            return false;
    }

    void transform(const glm::vec3 &translation = {0, 0, 0},
                   const glm::vec3 &rotation = {0, 0, 0},
                   const glm::vec3 &scale = {1, 1, 1})
    {
        glm::mat4 transformationMatrix = calculateTransformationMatrix(translation, rotation, scale);
        setTransformationMatrix(transformationMatrix);

        if (!(this->hasChildren()))
            return;
        for(int i =0;i<children.size();i++)
        {
            transformChildren(children[i], this->transfomrationMatrix);
        }
    }

    void transformChildren(TransformationComponent *parent, glm::mat4 transformationMatrix2)
    {
        //parent->transfomrationMatrix *= transformationMatrix2; // M
        parent->setTransformationMatrix(this->transfomrationMatrix * transformationMatrix2);
        // Base condition
        if (!(parent->hasChildren()))
            return;
        // General case
        for (int i = 0; i < parent->children.size(); i++)
            transformChildren(parent->children[i], parent->transfomrationMatrix);
    }
//    void transformChildren(TransformationComponent *parent, glm::mat4 &transformationMatrix2)
//    {
//        parent->transfomrationMatrix *= transformationMatrix2; // M
//        // el mafrood nenady setTransformationMatrix hena kaman 3alshan el childeren n-set feehom el value el sa7
//        //
//        // Base condition
//        if (!(this->hasChildren()))
//            return;
//        // General case
//        for (int i = 0; i < parent->children.size(); i++)
//            transformChildren(parent->children[i], transfomrationMatrix);
//    }

    const glm::mat4 getTransformationMatrix()
    {
        return transfomrationMatrix;
    }

    void setTransformationMatrix(glm::mat4 matrix)
    {
        this->transfomrationMatrix = matrix;
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
};

#endif