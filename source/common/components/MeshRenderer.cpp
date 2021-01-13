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
/*MeshRenderer *MeshRenderer::CreationFromBase()
{
}*/

void MeshRenderer::ReadData(string inputFile, int numOfEntities, vector<Material *> materialClassVec, vector<MeshRenderer *> &tcVector)
{
    Json::Value data;
    std::ifstream people_file(inputFile, std::ifstream::binary);
    people_file >> data;
    string entity = "entity";
    string entityTemp = "entity";
    for (int num = 1; num <= numOfEntities; num++)
    {
        entity += to_string(num);

        //last line in the for loop
        entity = entityTemp;
    }
}