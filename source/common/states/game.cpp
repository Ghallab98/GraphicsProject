#ifndef GAME_STATE_CPP
#define GAME_STATE_CPP

#include <vector>
#include <map>
#include <string.h>
using std::map;
using std::vector;
//
#include <texture/texture-utils.h>
#include "../texture2D.hpp"
#include <states/state.cpp>
#include <Renderer/RendererSystem.hpp>
#include <glm/glm.hpp>
#include "../sampler.hpp"

#define PI 3.1415926535897932384626433832795

class GameState : public State
{
    map<string, gameTemp::Mesh> models;
    vector<Entity *> entities;
    Entity *currentCamera;
    RendererSystem rendererSystem;
    //
    std::unordered_map<std::string, GLuint> textures;
    vector<gameTemp::Texture *> texVec;
    vector<gameTemp::Sampler *> sampVec;
    std::string current_texture_name;

public:
    GameState(Application *app = nullptr) : State(app)
    {
        name = "GameState";
    }

    void onEnter() override
    {
        // -- Initializing shaders
        programs["main"].create();
        programs["main"].attach("assets/shaders/transform.vert", GL_VERTEX_SHADER);
        programs["main"].attach("assets/shaders/tint.frag", GL_FRAGMENT_SHADER);
        programs["main"].link();
        //
        programs["text"].create();
        programs["text"].attach("assets/shaders/texture/transform.vert", GL_VERTEX_SHADER);
        programs["text"].attach("assets/shaders/texture/texture.frag", GL_FRAGMENT_SHADER);
        programs["text"].link();

        //////////////////////////////////////////////////////////////////////////////////////////////
        int numOfEntites = 0;
        string path = "./source/common/json_File/input.json";
        Component::ReadData(path, numOfEntites);
        cout << endl
             << endl
             << "Number of entitess " << numOfEntites << endl;
        //Creation of Entites
        for (int i = 0; i < numOfEntites; i++)
        {
            entities.push_back(new Entity);
        }
        //Transformation Component
        vector<TransformationComponent *> tcVector;
        TransformationComponent::ReadData(path, numOfEntites, tcVector);

        //ATTCHAING OF ALL COMPONENTS TO ENTITES (LAST THING TODO)
        for (int index = 0; index < numOfEntites; index++)
        {
            entities[index]->addComponent(tcVector[index]);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////
        //-- Loading a texture
        GLuint texture;
        gameTemp::Texture *text = new gameTemp::Texture();
        texture = text->getTexture();
        text->create(true, 0, 256, 128, 0, "assets/images/moon.jpg");
        current_texture_name = "moon";
        textures[current_texture_name] = texture;
        texVec.push_back(text);
        //tex 2
        GLuint texture2;
        gameTemp::Texture *text2 = new gameTemp::Texture();
        texture2 = text2->getTexture();
        text2->create(true, 0, 256, 128, 0, "assets/images/color-grid.png");
        current_texture_name = "color-grid";
        textures[current_texture_name] = texture2;
        texVec.push_back(text2);
        //text for the checker board
        GLuint texture3;
        gameTemp::Texture *text3 = new gameTemp::Texture();
        texture3 = text3->getTexture();
        text3->checkerBoard(texture3, {256, 256}, {128, 128}, {255, 255, 255, 255}, {16, 16, 16, 255});
        current_texture_name = "checkerboard";
        textures[current_texture_name] = texture3;
        texVec.push_back(text3);

        //--Loading a sampler
        GLuint glSampler;
        gameTemp::Sampler *sampler = new gameTemp::Sampler();
        glSampler = sampler->getSampler();
        sampler->create();
        sampVec.push_back(sampler);
        //sampler 2
        GLuint glSampler2;
        gameTemp::Sampler *sampler2 = new gameTemp::Sampler();
        glSampler2 = sampler2->getSampler();
        sampler2->create(GL_MIRROR_CLAMP_TO_EDGE);
        sampVec.push_back(sampler2);

        // -- Initializing mesh components
        gameTemp::mesh_utils::Cuboid(models["cuboid"], true);
        gameTemp::mesh_utils::Sphere(models["sphere"], {32, 16}, true);
        gameTemp::mesh_utils::Plane(models["plane"], {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

        Material *m1 = new Material(&programs["text"]);
        Material *m2 = new Material(&programs["text"]);
        Material *m3 = new Material(&programs["text"]);
        Material *m4 = new Material(&programs["main"]);
        //setting the texture and sampler of the material class with a value
        m1->setTexture(texVec[0]);
        m2->setTexture(texVec[1]);
        m3->setTexture(texVec[2]);
        m1->setSampler(sampVec[0]);
        m2->setSampler(sampVec[0]);
        m3->setSampler(sampVec[1]);
        //creation of a unifrom and ataching it to uniforms map
        glm::vec4 *tintVec = new glm::vec4(1, 1, 1, 0.8);
        glm::vec4 *tintVec2 = new glm::vec4(0.96, 0.9, 0.64, 1);
        m1->AddUniform<glm::vec4>("tint", tintVec);
        m2->AddUniform<glm::vec4>("tint", tintVec);
        m3->AddUniform<glm::vec4>("tint", tintVec2);
        m4->AddUniform<glm::vec4>("tint", tintVec);
        //With texture 1
        entities[2]->addComponent(new MeshRenderer(m1, &models["sphere"]));
        entities[3]->addComponent(new MeshRenderer(m4, &models["sphere"]));

        //With texture 2
        entities[0]->addComponent(new MeshRenderer(m2, &models["cuboid"]));
        entities[1]->addComponent(new MeshRenderer(m2, &models["cuboid"]));

        //With texture 3
        entities[4]->addComponent(new MeshRenderer(m3, &models["plane"]));

        //CREATE OBJECT PROPERTY OBj
        ObjectProperties *obj = new ObjectProperties();
        ObjectProperties *obj2 = new ObjectProperties();

        //CULLING INTIALZATIONS
        struct Culling myCull;
        myCull.enabled = true;
        myCull.cullFace = BACK;
        myCull.direction = CCW;
        //
        struct Culling myCull2;
        myCull.enabled = false;
        myCull.cullFace = BACK;
        myCull.direction = CCW;

        //BLENDING INITIALZATIONS
        struct Blending myBlend2;
        myBlend2.enabled = true;
        myBlend2.type = NotConstant;
        glm::vec4 blend_constant_color2 = {0.25f, 1.0f, 0.75f, 0.5f};
        myBlend2.destClr = blend_constant_color2;

        //CONSTANT BLENDING INTIALZATIONS
        struct Blending myBlend;
        myBlend.enabled = false;
        glm::vec4 blend_constant_color = {0.25f, 1.0f, 0.75f, 0.5f};
        myBlend.constClr = blend_constant_color;
        //Set blend and cull fo object properties
        obj->setCullObjProp(&myCull);
        obj2->setCullObjProp(&myCull2);
        obj->setBlendObjProp(&myBlend);
        obj2->setBlendObjProp(&myBlend2);
        //
        m1->setObjProp(obj);
        m2->setObjProp(obj);
        m3->setObjProp(obj);
        m4->setObjProp(obj2);

        // -- Initializing the camera
        CameraComponent *Cam = new CameraComponent;
        currentCamera = new Entity;
        currentCamera->addComponent(Cam);
        Cam->setEyePosition({10, 10, 10});
        Cam->setTarget({0, 0, 0});
        Cam->setUp({0, 1, 0});

        CameraControllerComponent *CamController = new CameraControllerComponent(app, currentCamera);
        currentCamera->addComponent(CamController);

        // -- Initializing GL
        glUseProgram(programs["text"]);
        rendererSystem.setEntitiesVector(&entities);
    }

    void onDraw(double deltaTime) override
    {
        // Texture
        glClear(GL_COLOR_BUFFER_BIT);

        // Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClearDepth(1.0f);
        glDepthMask(true);
        glColorMask(true, true, true, true);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentCamera->getCameraComponentController()->update(deltaTime);
        glm::mat4 camera_matrix = currentCamera->getCameraComponent()->getVPMatrix();

        rendererSystem.update(camera_matrix);
        rendererSystem.draw();
    }

    void onExit() override
    {
        //Reset the static number in Material class to 0
        Material toDestroy(nullptr);
        toDestroy.setIndex(0);

        //Destroy Textures
        for (int i = 0; i < texVec.size(); i++)
            delete texVec[i];

        //Destroy Samplers
        for (int i = 0; i < sampVec.size(); i++)
            delete sampVec[i];

        // Destroy entities
        for (int i = 0, numEntities = entities.size(); i < numEntities; i++)
            delete entities[i];

        entities.clear();

        // Destory mesh models
        for (auto it = models.begin(); it != models.end(); ++it)
            it->second.destroy();

        models.clear();

        State::onExit();
    }
};

#endif