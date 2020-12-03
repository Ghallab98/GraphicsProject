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

        std::cout << transformationMatrix[0][0] << " " << transformationMatrix[0][1] << " " << transformationMatrix[0][2] << " " << transformationMatrix[0][3] << endl;
        std::cout << transformationMatrix[1][0] << " " << transformationMatrix[1][1] << " " << transformationMatrix[1][2] << " " << transformationMatrix[1][3] << endl;
        std::cout << transformationMatrix[2][0] << " " << transformationMatrix[2][1] << " " << transformationMatrix[2][2] << " " << transformationMatrix[2][3] << endl;
        std::cout << transformationMatrix[3][0] << " " << transformationMatrix[3][1] << " " << transformationMatrix[3][2] << " " << transformationMatrix[3][3] << endl;
        std::cout << endl;
        transformChildren(this, transfomrationMatrix);
    }

    void transformChildren(TransformationComponent *parent, glm::mat4 &transformationMatrix2)
    {

        std::cout << transformationMatrix2[0][0] << " " << transformationMatrix2[0][1] << " " << transformationMatrix2[0][2] << " " << transformationMatrix2[0][3] << endl;
        std::cout << transformationMatrix2[1][0] << " " << transformationMatrix2[1][1] << " " << transformationMatrix2[1][2] << " " << transformationMatrix2[1][3] << endl;
        std::cout << transformationMatrix2[2][0] << " " << transformationMatrix2[2][1] << " " << transformationMatrix2[2][2] << " " << transformationMatrix2[2][3] << endl;
        std::cout << transformationMatrix2[3][0] << " " << transformationMatrix2[3][1] << " " << transformationMatrix2[3][2] << " " << transformationMatrix2[3][3] << endl;
        std::cout << endl;
        parent->transfomrationMatrix *= transformationMatrix2; // M
        glm::mat4 temp = parent->getTransformationMatrix();
        std::cout << temp[0][0] << " " << temp[0][1] << " " << temp[0][2] << " " << temp[0][3] << endl;
        std::cout << temp[1][0] << " " << temp[1][1] << " " << temp[1][2] << " " << temp[1][3] << endl;
        std::cout << temp[2][0] << " " << temp[2][1] << " " << temp[2][2] << " " << temp[2][3] << endl;
        std::cout << temp[3][0] << " " << temp[3][1] << " " << temp[3][2] << " " << temp[3][3] << endl;
        std::cout << endl;
        // Base condition
        if (!(parent->hasChildren()))
            return;

        // General case
        for (int i = 0; i < parent->children.size(); i++)
            transformChildren(parent->children[i], transfomrationMatrix);
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