#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include <glm/glm.hpp>
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>
#include <shader.hpp>
#include <component.hpp>

#include"./../materialClass/material.cpp"

using namespace gameTemp;

class MeshRenderer : public Component
{
private:
    Material* material;
    gameTemp::Mesh *pMesh;
public:
    MeshRenderer(Material* toBeAssignedMaterial,gameTemp::Mesh *pMesh);
    int getComponentType();
    void setMesh(gameTemp::Mesh *pMesh);
    const gameTemp::Mesh *getMesh();
    void Draw(glm::mat4 transformMatrix);
    ~MeshRenderer() {}
};

#endif