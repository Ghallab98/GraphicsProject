#ifndef GAME_STATE_CPP
#define GAME_STATE_CPP

#include <vector>
#include <map>
#include <string.h>
#include "../../../vendor/jsoncpp/include/json/value.h"
#include "../../../vendor/jsoncpp/include/json/json.h"
#include <fstream>
using std::map;
using std::vector;
//
#include "../texture/texture2D.hpp"
#include <states/state.cpp>
#include <Renderer/RendererSystem.hpp>
#include <glm/glm.hpp>
#include "../sampler.hpp"

#define PI 3.1415926535897932384626433832795

class GameState : public State
{
    map<string, gameTemp::Mesh> models;
    //
    vector<Entity *> entities;
    vector<TransformationComponent *> tcVector;
    vector<MeshRenderer *> meshRenderVector;
    //Light vector
    vector<LightComponent *> lightVec;
    vector<bool> isEntityLight;
    //Camera Controller Vars
    vector<CameraControllerComponent *> camControllerVector;
    vector<map<string, int>> CameraControllerComponentControllers; //map for each camera controller of the keys
    int currentCameraIndex;
    //Camera Vars
    vector<CameraComponent *> camVector;
    vector<bool> isEntityCamera;
    //
    vector<Entity *> currentCameraTempVecCtrl;
    Entity *currentCamera;
    vector<int> cameraCtrlPos; //camera controller position in entities array
    //
    RendererSystem rendererSystem;
    //Materials Vector Textures Map and Samplers Vector
    vector<Material *> materialVec;
    std::unordered_map<std::string, gameTemp::Texture *> textures;
    vector<gameTemp::Sampler *> sampVec;
    //Private fns
    static void ShaderInitializition(string inputFilepath, int &numOfShaders, vector<string> &programsName, vector<string> &vertexShaderPath, vector<string> &fragmentShaderPath, vector<bool> &isLightNeededVector)
    {
        string shaderName = "shader";
        string shaderNameTemp = "shader";
        Json::Value data;
        std::ifstream people_file(inputFilepath, std::ifstream::binary);
        people_file >> data;
        int shadersNum = data["Resources"]["Shaders"].size();
        numOfShaders = shadersNum;
        //
        for (int pos = 1; pos <= shadersNum; pos++)
        {
            bool isLightNeeded = false;
            shaderName += to_string(pos);
            programsName.push_back(shaderName);
            string vxPath = data["Resources"]["Shaders"][pos - 1][shaderName]["vertex"].asString();
            string frgPath = data["Resources"]["Shaders"][pos - 1][shaderName]["fragment"].asString();
            vertexShaderPath.push_back(vxPath);
            fragmentShaderPath.push_back(frgPath);
            if (data["Resources"]["Shaders"][pos - 1][shaderName]["isLightNeeded"])
            {
                if (data["Resources"]["Shaders"][pos - 1][shaderName]["isLightNeeded"].asBool() == true)
                {
                    isLightNeeded = true;
                }
            }
            isLightNeededVector.push_back(isLightNeeded);
            //last line
            shaderName = shaderNameTemp;
        }
    }
    static void MeshInitializition(string inputFilepath, map<string, gameTemp::Mesh> &models)
    {
        Json::Value data;
        std::ifstream people_file(inputFilepath, std::ifstream::binary);
        people_file >> data;
        int meshesNum = data["Resources"]["Meshes"].size();
        for (int i = 0; i < meshesNum; i++)
        {
            bool isLoadable = data["Resources"]["Meshes"][i]["isLoadable"].asBool();
            string meshName = data["Resources"]["Meshes"][i]["name"].asString();
            if (!isLoadable)
            {
                bool coloredFaces = data["Resources"]["Meshes"][i]["colored"].asBool();
                float center[3] = {0, 0, 0};
                if (data["Resources"]["Meshes"][i]["center"].size() != 0)
                {
                    center[0] = data["Resources"]["Meshes"][i]["center"][0].asFloat();
                    center[1] = data["Resources"]["Meshes"][i]["center"][1].asFloat();
                    center[2] = data["Resources"]["Meshes"][i]["center"][2].asFloat();
                }
                glm::vec3 centerVec = {center[0], center[1], center[2]};
                if (meshName == "cuboid")
                {
                    float size[3] = {1, 1, 1};
                    if (data["Resources"]["Meshes"][i]["size"].size() != 0)
                    {
                        size[0] = data["Resources"]["Meshes"][i]["size"][0].asFloat();
                        size[1] = data["Resources"]["Meshes"][i]["size"][1].asFloat();
                        size[2] = data["Resources"]["Meshes"][i]["size"][2].asFloat();
                    }
                    glm::vec3 sizeVec = {size[0], size[1], size[2]};
                    gameTemp::mesh_utils::Cuboid(models["cuboid"], coloredFaces, centerVec, sizeVec);
                }
                else if (meshName == "sphere")
                {
                    float raduis = data["Resources"]["Meshes"][i]["radius"].asFloat();
                    gameTemp::mesh_utils::Sphere(models["sphere"], coloredFaces, centerVec, raduis);
                }
                else if (meshName == "plane")
                {
                    float resolution[2] = {1, 1};
                    float sizeP[2] = {1, 1};
                    float texOffSet[2] = {0, 0};
                    float texTiling[2] = {1, 1};
                    if (data["Resources"]["Meshes"][i]["resolution"].size() != 0)
                    {
                        resolution[0] = data["Resources"]["Meshes"][i]["resolution"][0].asFloat();
                        resolution[1] = data["Resources"]["Meshes"][i]["resolution"][1].asFloat();
                    }
                    glm::vec2 resVector = {resolution[0], resolution[1]};
                    if (data["Resources"]["Meshes"][i]["size"].size() != 0)
                    {
                        sizeP[0] = data["Resources"]["Meshes"][i]["size"][0].asFloat();
                        sizeP[1] = data["Resources"]["Meshes"][i]["size"][1].asFloat();
                    }
                    glm::vec2 resSizeP = {sizeP[0], sizeP[1]};
                    if (data["Resources"]["Meshes"][i]["texture offset"].size() != 0)
                    {
                        texOffSet[0] = data["Resources"]["Meshes"][i]["texture offset"][0].asFloat();
                        texOffSet[1] = data["Resources"]["Meshes"][i]["texture offset"][1].asFloat();
                    }
                    glm ::vec2 texOffVec = {texOffSet[0], texOffSet[1]};
                    if (data["Resources"]["Meshes"][i]["texture tiling"].size() != 0)
                    {
                        texTiling[0] = data["Resources"]["Meshes"][i]["texture tiling"][0].asFloat();
                        texTiling[1] = data["Resources"]["Meshes"][i]["texture tiling"][1].asFloat();
                    }
                    glm ::vec2 texTileVector = {texTiling[0], texTiling[1]};
                    gameTemp::mesh_utils::Plane(models["plane"], resVector, coloredFaces, centerVec, resSizeP, texOffVec, texTileVector);
                }
            }
            else
            {
                string path = data["Resources"]["Meshes"][i]["path"].asString();
                gameTemp::mesh_utils::loadOBJ(models[meshName], path.c_str());
            }
        }
    }

public:
    GameState(Application *app = nullptr) : State(app)
    {
        name = "GameState";
    }

    void onEnter() override
    {
        string path = "./assets/files/input.json";
        vector<string> programsName;
        vector<string> vertexShaderPath;
        vector<string> fragmentShaderPath;
        vector<bool> isLightNeededVector;
        int numOfShaders;
        ShaderInitializition(path, numOfShaders, programsName, vertexShaderPath, fragmentShaderPath, isLightNeededVector);
        MeshInitializition(path, models);
        for (int i = 0; i < numOfShaders; i++)
        {
            programs[programsName[i]].create();
            programs[programsName[i]].attach(vertexShaderPath[i], GL_VERTEX_SHADER);
            programs[programsName[i]].attach(fragmentShaderPath[i], GL_FRAGMENT_SHADER);
            programs[programsName[i]].link();
            if (isLightNeededVector[i]) //shader takes light
            {
                programs[programsName[i]].enableLightEffect();
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////
        int numOfEntities = 0;
        int numOfCamEntities = 0;
        int numOfCamCtrls = 0;
        int numOfLights = 0;
        Component::ReadData(path, numOfEntities, numOfCamEntities, numOfCamCtrls, numOfLights);
        //Creation of Entites and Camera Entites and Light entities
        for (int i = 0; i < numOfEntities + numOfCamEntities + numOfLights; i++)
        {
            entities.push_back(new Entity);
        }
        //--Transformation Component
        TransformationComponent::ReadData(path, numOfEntities + numOfCamEntities + numOfLights, tcVector);
        //--Camera Component
        CameraComponent ::ReadData(path, numOfEntities + numOfCamEntities + numOfLights, camVector, isEntityCamera);
        //--Light Component
        LightComponent ::ReadData(path, numOfEntities + numOfCamEntities + numOfLights, lightVec, isEntityLight);
        //ATTCHAING OF ALL TRANSOFRMATION COMPONENTS AND CAMERA COMPONENTS AND LIGHT COMPONENTS TO ENTITES+
        for (int index = 0; index < numOfEntities + numOfCamEntities + numOfLights; index++)
        {
            entities[index]->addComponent(tcVector[index]);
            entities[index]->addComponent(camVector[index]);
            entities[index]->addComponent(lightVec[index]);
        }
        //THIS BLOCK IS AFTER ATTACHING CAMERA COMPONENT TO ENTITIES FOR USAGE IN CAMERA CONTROLLER CONSTRUCTOR
        //--Camera Controller Component
        CameraControllerComponent::ReadData(path, entities, camControllerVector, app, cameraCtrlPos, CameraControllerComponentControllers);
        //cout << "The camera ctrl pos size isss  " << cameraCtrlPos.size() << endl;

        int itIndex = 0;
        for (int i = 0; i < camControllerVector.size(); i++)
        {
            currentCameraTempVecCtrl.push_back(entities[cameraCtrlPos[itIndex]]);
            entities[cameraCtrlPos[itIndex]]->addComponent(camControllerVector[i]);
            itIndex++;
        }
        //-- SET THE CURRENT CAMERA AS THE FIRST CAMERA ENTITY IN THE VECTOR AND THE CURRENT CAMERA INDEX IN THE VECTOR TO 0 (CHANGED ACCORDING TO THE LOGIC IN THE GAME)
        currentCamera = currentCameraTempVecCtrl[0];
        currentCameraIndex = 0;
        //

        //////////////////////////////////////////////////////////////////////////////////////////////
        //Textures
        gameTemp::Texture ::ReadData(path, textures);
        //Samplers
        gameTemp::Sampler::ReadData(path, sampVec);
        //Material
        Material::ReadData(path, textures, sampVec, programs, materialVec);
        //Mesh Rendrer
        MeshRenderer ::ReadData(path, numOfEntities + numOfCamEntities, models, materialVec, meshRenderVector);
        //Adding Mesh Renderer component to entites
        for (int l = 0; l < meshRenderVector.size(); l++)
        {
            entities[l]->addComponent(meshRenderVector[l]);
        }
        ///////////////////////////////////////////////////////////////////////
        glm::vec4 *tintVec = new glm::vec4(1, 1, 1, 0.8);
        glm::vec4 *tintVec2 = new glm::vec4(0.96, 0.9, 0.64, 1);
        materialVec[0]->AddUniform<glm::vec4>("tint", tintVec);
        materialVec[1]->AddUniform<glm::vec4>("tint", tintVec);
        materialVec[2]->AddUniform<glm::vec4>("tint", tintVec2);
        materialVec[3]->AddUniform<glm::vec4>("tint", tintVec);
        ///////////////////////////////////////////////////////////////////////

        // -- Initializing GL
        glUseProgram(programs[programsName[1]]);
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
        // TODO --CHOOSE WHICH CAMERA ENTITY TO BE THE CURRENT CAMERA ACCORDING TO THE GAME LOGIC
        int front = CameraControllerComponentControllers[currentCameraIndex]["front"];
        int back = CameraControllerComponentControllers[currentCameraIndex]["back"];
        int right = CameraControllerComponentControllers[currentCameraIndex]["right"];
        int left = CameraControllerComponentControllers[currentCameraIndex]["left"];
        int jump = CameraControllerComponentControllers[currentCameraIndex]["jump"];
        int crouch = CameraControllerComponentControllers[currentCameraIndex]["crouch"];
        /*cout << "The front is " << front << endl
             << endl;
        cout << "The back is " << back << endl
             << endl;
        cout << "The right is " << right << endl
             << endl;
        cout << "The left is " << left << endl
             << endl;
        cout << "The jump is " << jump << endl
             << endl;
        cout << "The crouch is " << crouch << endl
             << endl;*/
        currentCamera->getCameraComponentController()->update(deltaTime, front, back, right, left, jump, crouch);
        glm::mat4 camera_matrix = currentCamera->getCameraComponent()->getVPMatrix();
        //

        rendererSystem.update(camera_matrix, programs);
        rendererSystem.draw(currentCamera);
    }

    void onExit() override
    {
        //Destroy Transformation Component Vector
        for (int i = 0; i < tcVector.size(); i++)
        {
            delete tcVector[i];
        }
        //Destroy Mesh Renderer Vector
        for (int i = 0; i < meshRenderVector.size(); i++)
        {
            delete meshRenderVector[i];
        }
        //Destroy Camera Components Vector and the isCameraEntity vector will be deleted automatically
        for (int i = 0; i < camVector.size(); i++)
        {
            delete camVector[i];
        }
        // Delete the current Camera Entity
        delete currentCamera;
        //Delete the Vector of cameras that is controlled by Camera/Movement Controller
        for (int i = 0; i < currentCameraTempVecCtrl.size(); i++)
        {
            delete currentCameraTempVecCtrl[i];
        }
        //Delete Camera Controllers Vector
        for (int i = 0; i < camControllerVector.size(); i++)
        {
            delete camControllerVector[i];
        }
        //CameraControllerComponentControllers will be automatically deleted
        //Destroy Textures
        for (auto &it : textures)
        {
            delete it.second;
        }
        textures.clear();
        //Destroy Samplers
        for (int i = 0; i < sampVec.size(); i++)
            delete sampVec[i];
        //Delete Material Vectors
        for (int i = 0; i < materialVec.size(); i++)
        {
            delete materialVec[i];
        }
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