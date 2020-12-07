#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include <glm/glm.hpp>
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>
#include <shader.hpp>
#include <component.hpp>

#define CUBOID 0
#define PLANE 1
#define SPHERE 2
#define OTHER 3

using namespace gameTemp;

class MeshRenderer : public Component
{
private:
    gameTemp::ShaderProgram *program;
    gameTemp::Mesh *pMesh;

public:
    MeshRenderer(gameTemp::Mesh *pMesh = nullptr, gameTemp::ShaderProgram *program = nullptr)
    {
        this->pMesh = pMesh;
        this->program = program;
    }

    void setMesh(gameTemp::Mesh *pMesh)
    {
        this->pMesh = pMesh;
    }

    const gameTemp::Mesh *getMesh()
    {
        return this->pMesh;
    }

    void setProgram(gameTemp::ShaderProgram *program)
    {
        this->program = program;
    }

    void Draw(glm::mat4 transformMatrix)
    {
        glUseProgram(*program);
        program->set("tint", glm::vec4(1, 1, 1, 1));
        program->set("transform", transformMatrix);
        pMesh->draw();
    }
};

#endif