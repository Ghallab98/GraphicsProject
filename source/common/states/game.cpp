#ifndef GAME_STATE_CPP
#define GAME_STATE_CPP

#include<vector>
#include <map>
using std::map;
using std::vector;
//
#include "../texture2D.hpp"
#include <states/state.cpp>
#include <Renderer/RendererSystem.hpp>
#include <glm/glm.hpp>
#include"./../sampler.hpp"



#define PI 3.1415926535897932384626433832795

class GameState : public State
{
    map<string, gameTemp::Mesh> models;
    vector<Entity *> entities;
    Entity *currentCamera;
    RendererSystem rendererSystem;
    //
    std::unordered_map<std::string, GLuint> textures;
    vector<gameTemp:: Texture> texVec;
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

        // -- Initializing entities
        Entity *cubeParent = new Entity;
        Entity *cubeChild = new Entity;
        Entity *sphere = new Entity;
        Entity *yo = new Entity;

        //-- Loading a texture
        GLuint texture;
        gameTemp::Texture text;
        texture= text.getTexture();
        text.create(texture,true,0,256,128,0,"assets/images/moon.jpg");
        current_texture_name = "moon";
        textures[current_texture_name] = texture;
        texVec.push_back(text);
        //tex 2
        GLuint texture2;
        gameTemp::Texture text2;
        texture2= text2.getTexture();
        text2.create(texture2,true,0,256,128,0,"assets/images/color-grid.png");
        current_texture_name = "color-grid";
        textures[current_texture_name] = texture2;
        texVec.push_back(text2);
        
        //--Loading a sampler
        GLuint glSampler;
        gameTemp::Sampler sampler;
        glSampler = sampler.getSampler();
        sampler.create(glSampler);


        // -- Initializing mesh components
        gameTemp::mesh_utils::Cuboid(models["cuboid"], true);
        gameTemp::mesh_utils::Sphere(models["sphere"], {32, 16}, true);

        Material *m1 = new Material(&programs["text"]);
        Material *m2 = new Material(&programs["text"]);

        //setting the texture of the material class with a value
        m1->setTexture(texture);
        m2->setTexture(texture2);
        m1->setSampler(glSampler);
        m2->setSampler(glSampler);

        //creation of a unifrom and ataching it to uniforms map
        glm::vec4 *tintVec = new glm::vec4(1, 1, 1, 0.8);
        m1->AddUniform<glm::vec4>(tint, tintVec);
        m2->AddUniform<glm::vec4>(tint, tintVec);

        //With texture 
        sphere->addComponent(new MeshRenderer(m1, &models["sphere"]));
        yo->addComponent(new MeshRenderer(m1, &models["sphere"]));

        //Without texture 
        cubeParent->addComponent(new MeshRenderer(m2, &models["cuboid"]));
        cubeChild->addComponent(new MeshRenderer(m2, &models["cuboid"]));

        //CREATE OBJECT PROPERTY OBj
        ObjectProperties *obj = new ObjectProperties();
        //CULLING INTIALZATIONS
        struct Culling myCull;
        myCull.enabled = true;
        myCull.cullFace = BACK;
        myCull.direction = CCW;
        obj->setCullObjProp(&myCull);

        //BLENDING INITIALZATIONS
        struct Blending myBlend;
        myBlend.enabled = true;
        myBlend.type = NotConstant;
        glm::vec4 blend_constant_color = {0.25f, 1.0f, 0.75f, 0.5f};
        myBlend.destClr = blend_constant_color;
        obj->setBlendObjProp(&myBlend);
        
        //CONSTANT BLENDING INTIALZATIONS
        // struct Blending myBlend2;
        // myBlend2.enabled=true;
        // glm::vec4 blend_constant_color = {0.25f,1.0f,0.75f,0.5f};
        // myBlend2.constClr = blend_constant_color;
        // cubeChild->setBlendObjProp(&myBlend2);
        //
        m1->setObjProp(obj);
        m2->setObjProp(obj);

        // -- Initializing transformation components
        TransformationComponent *TCcubeParent = new TransformationComponent(nullptr);
        TransformationComponent *TCcubeChild = new TransformationComponent(TCcubeParent);
        TransformationComponent *TCSphere = new TransformationComponent(TCcubeChild);
        TransformationComponent *TCyo = new TransformationComponent(nullptr);

        cubeParent->addComponent(TCcubeParent);
        cubeChild->addComponent(TCcubeChild);
        sphere->addComponent(TCSphere);
        yo->addComponent(TCyo);

        cubeParent->getTransformationComponent()->transform({-2, 1, -2}, {0, 0, 0}, {2, 2, 2});
        yo->getTransformationComponent()->transform({-2, 2, -2}, {0, 0, 0}, {2, 2, 2});
        cubeChild->getTransformationComponent()->transform({2, 2, -2}, {0, 0, 0}, {1, 1, 1});
        sphere->getTransformationComponent()->transform({-2, 1, 2}, {0, 0, 0}, {2, 2, 2});

        // -- Storing entities
        entities.push_back(cubeParent);
        entities.push_back(cubeChild);
        entities.push_back(sphere);
        entities.push_back(yo);

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
        for (int i=0 ; i<texVec.size();i++)
            texVec[i].destroy();

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