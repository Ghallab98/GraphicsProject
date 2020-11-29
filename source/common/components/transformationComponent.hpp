#ifndef TRANSFORMATION_COMPONENT_HPP
#define TRANSFORMATION_COMPONENT_HPP

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "./component.hpp"

class TransformationComponent : Component
{
private:
    TransformationComponent *parent;
    glm::mat4 transfomrationMatrix = glm::mat4(1.0f);

public:
    transformationComponent(TransformationComponent *myParent)
    {
        parent = myParent;
    }

    void transform(const glm::vec3 &translation = {0, 0, 0},
                   const glm::vec3 &rotation = {0, 0, 0},
                   const glm::vec3 &scale = {1, 1, 1})
    {
        glm::mat4 transformationMatrix = getTransformationMatrix(translation, rotation, scale);
        this->transfomrationMatrix = transformationMatrix;
    }

    static glm::mat4 getTransformationMatrix(
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