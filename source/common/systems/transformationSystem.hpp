#ifndef TRANSFORMATION_SYSTEM_HPP
#define TRANSFORMATION_SYSTEM_HPP

#include "../components/transformationComponent.hpp"

class TransformationSystem {

    TransformationSystem(){}

    static void TransformPos(struct transformationComponent *component, const glm::mat4& tranformationMatrix ) {
        component->position *= tranformationMatrix;
    }

    static glm::mat4 getTransformationMatrix(
        const glm::vec3& translation = {0,0,0},
        const glm::vec3& rotation = {0,0,0},
        const glm::vec3& scale = {1,1,1}
    ){
        return  glm::translate(glm::mat4(1.0f), translation) *
                glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
                glm::scale(glm::mat4(1.0f), scale);
    }
    
};

#endif