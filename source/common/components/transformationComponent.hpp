#ifndef TRANSFORMATION_COMPONENT_HPP
#define TRANSFORMATION_COMPONENT_HPP

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <vector>

#include "./component.hpp"

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
            this->transfomrationMatrix = parent->transfomrationMatrix;
        }
        else
            transfomrationMatrix = glm::mat4(1.0f);
    }

    bool hasChildren()
    {
        return children.size() == 0;
    }

    void transform(const glm::vec3 &translation = {0, 0, 0},
                   const glm::vec3 &rotation = {0, 0, 0},
                   const glm::vec3 &scale = {1, 1, 1})
    {
        glm::mat4 transformationMatrix = calculateTransformationMatrix(translation, rotation, scale);
        tranformChildren(this, transfomrationMatrix);
    }

    void tranformChildren(TransformationComponent *parent, glm::mat4 &transformationMatrix)
    {
        parent->transfomrationMatrix *= transformationMatrix; // M

        // Base condition
        if (!(parent->hasChildren()))
            return;

        // General case
        for (int i = 0; i < parent->children.size(); i++)
            tranformChildren(parent->children[i], transfomrationMatrix);
    }

    const glm::mat4 getTransformationMatrix()
    {
        return transfomrationMatrix;
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