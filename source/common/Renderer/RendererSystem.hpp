#ifndef RENDERER_SYSTEM_HPP
#define RENDERER_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include <string>
#include <entities/entity.hpp>
#include <light.cpp>
#include <Renderer/MeshRenderCommand.hpp>
#include <shader.hpp>

using std::vector;

class RendererSystem
{
    vector<Entity *> *entities;
    vector<struct MeshRenderCommand> renderCommands;

    void handleCulling(struct Culling *cull)
    {
        if (!cull)
            return;

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
        if (!blend)
            return;

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

    void update(glm::mat4 cameraMatrix, map<string, ShaderProgram> &programs)
    {
        int light_index = 0;
        renderCommands.clear();
        for (int i = 0, numEntities = entities->size(); i < numEntities; i++)
        {
            LightComponent *lightComponent = (*entities)[i]->getLightComponent();
            if (lightComponent)
            {
                for (auto &it : programs)
                {
                    if (it.second.isLightNeeded())
                        lightComponent->configureShader(light_index, cameraMatrix, &(it.second));
                }
                light_index++;
            }

            MeshRenderer *meshRenderer = (*entities)[i]->getMeshRendrer();
            if (!meshRenderer)
                continue;

            renderCommands.push_back(meshRenderer->getRenderCommand(cameraMatrix));
        }

        std::sort(std::begin(renderCommands), std::end(renderCommands));
    }

    void draw(Entity *currentCamera)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0, numCommands = renderCommands.size(); i < numCommands; i++)
        {
            gameTemp::ShaderProgram *program = renderCommands[i].material->getShaderProgram();
            glUseProgram(*program);
            renderCommands[i].material->setProgramUniforms();
            program->set("object_to_world", renderCommands[i].transformation);
            program->set("object_to_world_inv_transpose", glm::inverse(renderCommands[i].transformation), true);
            program->set("view_projection", currentCamera->getCameraComponent()->getVPMatrix());
            program->set("camera_position", currentCamera->getCameraComponent()->getEyePosition());

            ObjectProperties *objProp = renderCommands[i].material->getObjProp();
            handleCulling(objProp->getCull());
            handleBlending(objProp->getBlend());

            renderCommands[i].material->activateUnitTextures();
            renderCommands[i].mesh->draw();
        }
    }
};

#endif