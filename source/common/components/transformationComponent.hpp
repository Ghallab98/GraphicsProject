#ifndef TRANSFORMATION_COMPONENT_HPP
#define TRANSFORMATION_COMPONENT_HPP

#include <glm/glm.hpp>

class transformationComponent
{
private:
    transformationComponent *parent;
    glm::mat4 position;

public:
    transformationComponent(transformationComponent myParent, glm::mat4 initialPos) : parent(&myParent), position(initialPos){};

    /*void transform(struct transformationComponent *component, const glm::mat4 &transformationMatrix)
    {
        this->position *= transformationMatrix;
    }*/

    void transform(const glm::vec3 &translation = {0, 0, 0},
                   const glm::vec3 &rotation = {0, 0, 0},
                   const glm::vec3 &scale = {1, 1, 1})
    {
        glm::mat4 transformationMatrix = getTransformationMatrix(translation, rotation, scale);
        this->position *= transformationMatrix;
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