#include "MeshRenderer.hpp"

MeshRenderer::MeshRenderer(Material *toBeAssignedMaterial, gameTemp::Mesh *pMesh)
{
    this->material = toBeAssignedMaterial;
    this->pMesh = pMesh;
}

int MeshRenderer::getComponentType()
{
    return MESH_RENDERER_COMPONENT;
}

void MeshRenderer::setMesh(gameTemp::Mesh *pMesh)
{
    this->pMesh = pMesh;
}

gameTemp::Mesh *MeshRenderer::getMesh()
{
    return this->pMesh;
}

MeshRenderCommand MeshRenderer::getRenderCommand(const glm::mat4 &cameraMatrix)
{
    glm::mat4 transformation = cameraMatrix * myEntity->getTransformationComponent()->getTransformationMatrix();
    glm::vec4 tranformed_origin = transformation * glm::vec4(0, 0, 0, 1);

    return {
        material,
        tranformed_origin.z,
        transformation,
        pMesh};
}

//
MeshRenderer *MeshRenderer::CreationFromBase()
{
    //MeshRenderer *createdMeshRend = new MeshRenderer();
    //return createdMeshRend;
    return nullptr;
}