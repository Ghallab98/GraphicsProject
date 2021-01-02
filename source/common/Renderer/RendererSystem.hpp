#ifndef RENDERER_SYSTEM_HPP
#define RENDERER_SYSTEM_HPP

#include <entities/entity.hpp>
#include <vector>

using std::vector;

class RendererSystem
{
    vector<Entity *> *Entities;

public:
    RendererSystem() : Entities(nullptr) {}
    RendererSystem(vector<Entity *> *Entities) : Entities(Entities) {}

    bool isInitialized()
    {
        return Entities != nullptr;
    }

    void setEntitiesVector(vector<Entity *> *Entities)
    {
        this->Entities = Entities;
    }

    void update(glm::mat4 cameraMatrix)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        for (int i = 0; i < Entities->size(); i++)
        {
            if (!(*Entities)[i]->getMeshRendrer())
                continue;

            TransformationComponent *TC = (*Entities)[i]->getTransformationComponent();
            glm::mat4 transformationMatrix = TC->getTransformationMatrix();
            MeshRenderer *R = (*Entities)[i]->getMeshRendrer();
            glm::mat4 matrix = cameraMatrix * transformationMatrix;
            R->Draw(matrix);
        }
    }
};

#endif