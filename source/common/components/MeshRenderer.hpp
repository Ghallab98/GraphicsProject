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

    int getComponentType()
    {
        return MESH_RENDERER_COMPONENT;
    }

    void setMesh(gameTemp::Mesh *pMesh)
    {
        this->pMesh = pMesh;
    }

    const gameTemp::Mesh *getMesh()
    {
        return this->pMesh;
    }

    void setProgram(gameTemp::ShaderProgram *program , bool isCulling)
    {
        this->program = program;
    }

    void Draw(glm::mat4 transformMatrix , ObjectProperties objProp)
    {
        glUseProgram(*program);
        program->set("tint", glm::vec4(1, 1, 1, 0.8));
        program->set("transform", transformMatrix);
        //CULLING
        if(objProp.cull.enabled){
            glEnable(GL_CULL_FACE);
            if(objProp.cull.cullFace==FRONT)
                    glCullFace(GL_FRONT);
                else if(objProp.cull.cullFace==BACK)
                    glCullFace(GL_BACK);
            if(objProp.cull.direction==CCW)
                glFrontFace(GL_CCW);
            else
                glFrontFace(GL_CW);
        }    
        else
            glDisable(GL_CULL_FACE);
        //BLENDING
        if(objProp.blend.enabled){
            if(objProp.blend.type==Constant){
                glEnable(GL_BLEND);
                glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR);
                glBlendColor(objProp.blend.constClr.r,objProp.blend.constClr.g, objProp.blend.constClr.b, objProp.blend.constClr.a);
            }
            else if(objProp.blend.type==NotConstant){
                glEnable(GL_BLEND);
                glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }
        }
        else
             glDisable(GL_BLEND);
        pMesh->draw();
    }

    ~MeshRenderer() {}
};

#endif