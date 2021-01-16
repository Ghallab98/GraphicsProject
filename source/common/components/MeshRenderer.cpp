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
    glm::mat4 transformation = myEntity->getTransformationComponent()->getTransformationMatrix();
    glm::vec4 tranformed_origin = cameraMatrix * transformation * glm::vec4(0, 0, 0, 1);

    return {
        material,
        tranformed_origin.z,
        transformation,
        pMesh};
}

//
MeshRenderer *MeshRenderer::CreationFromBase(gameTemp::Mesh *myMesh, Material *myMaterial)
{
    MeshRenderer *meshPtr = new MeshRenderer(myMaterial, myMesh);
    return meshPtr;
}
//Read Data
void MeshRenderer::ReadData(string inputPath, int numOfEntities, map<string, gameTemp::Mesh> &models, vector<Material *> &materialVec, vector<MeshRenderer *> &meshRendVector)
{
    Json::Value data;
    std::ifstream people_file(inputPath, std::ifstream::binary);
    people_file >> data;
    string entity = "entity";
    string entityTemp = "entity";
    for (int pos = 1; pos <= numOfEntities; pos++)
    {
        entity += to_string(pos);
        if (data["World"][entity]["Mesh Renderer"])
        {
            int materialNum = data["World"][entity]["Mesh Renderer"]["material"].asInt() - 1;
            string meshName = data["World"][entity]["Mesh Renderer"]["mesh"].asString();
            meshRendVector.push_back(CreationFromBase(&models[meshName], materialVec[materialNum]));
        }
        else
        {
            meshRendVector.push_back(nullptr);
        }
        //last line
        entity = entityTemp;
    }
}