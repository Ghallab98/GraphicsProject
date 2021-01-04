#ifndef RENDERER_SYSTEM_HPP
#define RENDERER_SYSTEM_HPP

#include <vector>
#include <algorithm>

#include <entities/entity.hpp>
#include <Renderer/MeshRenderCommand.hpp>
#include <shader.hpp>

using std::vector;


class RendererSystem
{
    vector<Entity *> *entities;
    vector<struct MeshRenderCommand> renderCommands;

    void handleCulling(struct Culling *cull)
    {
        if (!(cull->enabled))
        {
            glDisable(GL_CULL_FACE);
            return;
        }

        glEnable(GL_CULL_FACE);
        if (cull->cullFace == FRONT)
            glCullFace(GL_FRONT);

        else if (cull->cullFace == BACK)
            glCullFace(GL_BACK);

        if (cull->direction == CCW)
            glFrontFace(GL_CCW);

        else
            glFrontFace(GL_CW);
    }

    void handleBlending(struct Blending *blend)
    {
        if (!(blend->enabled))
        {
            glDisable(GL_BLEND);
            return;
        }

        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        if (blend->type == Constant)
        {
            glBlendFunc(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR);
            glBlendColor(blend->constClr.r,
                         blend->constClr.g,
                         blend->constClr.b,
                         blend->constClr.a);
        }
        else if (blend->type == NotConstant)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    }
    void handleTexture(Material * mtr){
            GLuint texture = mtr->getTexture();
            GLuint sampler = mtr->getSampler();
        if(texture != -1) {
            int i= mtr->getIndex();
            glBindTexture(GL_TEXTURE_2D, texture);
            glActiveTexture(GL_TEXTURE0); // GL_TEXTURE0+i

            if(sampler != -1)
                    glBindSampler(GL_TEXTURE0, sampler); // GL_TEXTURE0+i

            mtr->getShaderProgram()->set("sampler",GL_TEXTURE0+i );
        }
    }

public:
    RendererSystem() : entities(nullptr) {}
    RendererSystem(vector<Entity *> *Entities) : entities(Entities) {}

    bool isInitialized()
    {
        return entities != nullptr;
    }

    void setEntitiesVector(vector<Entity *> *Entities)
    {
        this->entities = Entities;
    }

    void update(glm::mat4 cameraMatrix)
    {
        renderCommands.clear();
        for (int i = 0, numEntities = entities->size(); i < numEntities; i++)
        {
            MeshRenderer *meshRenderer = (*entities)[i]->getMeshRendrer();
            if (!meshRenderer)
                continue;

            renderCommands.push_back(meshRenderer->getRenderCommand(cameraMatrix));
        }

        std::sort(std::begin(renderCommands), std::end(renderCommands));
    }

    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0, numCommands = renderCommands.size(); i < numCommands; i++)
        {
            gameTemp::ShaderProgram *program = renderCommands[i].material->getShaderProgram();
            glUseProgram(*program);

            program->set("tint", *(renderCommands[i].material->getTint()));
            program->set("transform", renderCommands[i].transformation);

            ObjectProperties *objProp = renderCommands[i].material->getObjProp();

            handleCulling(objProp->getCull());
            handleBlending(objProp->getBlend());
            handleTexture(renderCommands[i].material);

            renderCommands[i].mesh->draw();
        }
    }
};

#endif