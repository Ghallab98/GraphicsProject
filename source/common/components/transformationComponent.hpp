#ifndef TRANSFORMATION_COMPONENT_HPP
#define TRANSFORMATION_COMPONENT_HPP

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
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
    //TO BE CALLED FROM THE READ FILE FN IN THE COMPONENT FILE
    static TransformationComponent *CreationFromBase(TransformationComponent *parent, glm::vec3 translation, glm ::vec3 rotation, glm::vec3 scaling)
    {
        TransformationComponent *TC_Comp = new TransformationComponent(parent);
        TC_Comp->transform(translation, rotation, scaling);
    }
};

#endif