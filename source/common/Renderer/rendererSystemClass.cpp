#define TRANFORMATION_COMPONENT 0
#define RENDER_COMPONENT 1
#define CAMERA_COMPONENT 2
#define PHYSICS_COMPONENT 3
#include <entities/entity.hpp>

void rendererSystem(vector<Entity*> Entities)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<Entities.size();i++)
    {
        glm::mat4 transformationMatrix = Entities[i]->getComponent(TransformationComponent*)->transformationMatrix;
        glm::mat4 cameraMatrix = Entities[i]->getComponent(CAMERA_COMPONENT)->cameraMatrix;

        glm::mat4 matrix = cameraMatrix * transformationMatrix;

        Entities[i]->getComponent(RENDER_COMPONENT)->Draw(matrix);
    }    
}