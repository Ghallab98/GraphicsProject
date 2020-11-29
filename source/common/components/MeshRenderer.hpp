#ifndef MESHRENDERER_HPP
#define MESHRENDERER_HPP
#include <glm/glm.hpp>
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>
#include <shader.hpp>
#include "./component.hpp"

#define CUBOID 0
#define PLANE 1
#define SPHERE 2
#define OTHER 3

class MeshRenderer : Component
{
    private:
        Mesh* pMesh;
        ShaderProgram* program;
        Entity* myEntity;
    public:
        MeshRenderer(Mesh* pMesh, ShaderProgram* program,Entity* myEntity)
        {
            this->pMesh = pMesh;
            this->program = program;
            this->myEntity = myEntity;
            Set();
        }
        void Draw(glm::mat4 transformMatrix) override
        {
            glUseProgram(&program);

            program->set("tint", glm::vec4(1,1,1,1));
            program->set("transform", transformMatrix);
            pMesh->draw();
        }
        void Set()
        {
            switch (myEntity->myType){
                case CUBOID: 
                    mesh_utils::Cuboid(&pMesh,true);
                    break;
                case PLANE: 
                    mesh_utils::Plane(&pMesh, {1,1}, true);
                    break;
                case SPHERE:
                    mesh_utils::Sphere(&pMesh, {32,16},true);
                    break;
                case OTHER:
                    mesh_utils::loadOBJ(&pMesh, myEntity->filePath);
                    break;
            }
        }
};

#endif