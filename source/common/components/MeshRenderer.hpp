#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include <glm/glm.hpp>
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>
#include <shader.hpp>
#include <component.hpp>
#include <entities/entity.hpp>
#include <components/transformationComponent.hpp>
#include <Renderer/MeshRenderCommand.hpp>
#include <materialClass/material.hpp>

class MeshRenderer : public Component
{
private:
    Material *material;
    gameTemp::Mesh *pMesh;
    static MeshRenderer *CreationFromBase();

public:
    MeshRenderer(Material *toBeAssignedMaterial, gameTemp::Mesh *pMesh);

    int getComponentType();
    gameTemp::Mesh *getMesh();
    MeshRenderCommand getRenderCommand(const glm::mat4 &cameraMatrix);

    void setMesh(gameTemp::Mesh *pMesh);
    //
    static void ReadData(string inputFile, int numOfEntities, vector<Material *> materialClassVec, vector<MeshRenderer *> &tcVector);

    ~MeshRenderer() {}
};

#endif