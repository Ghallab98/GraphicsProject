#include "./material.hpp"

Material::Material(gameTemp::ShaderProgram *specifiedShader)
{
    shaderPtr = specifiedShader;
}

void Material::setShaderProgram(gameTemp::ShaderProgram *specifiedShader)
{
    shaderPtr = specifiedShader;
}
//
void Material::addUnitTexture(unitTexture unit_texture)
{
    unitTextures.push_back(unit_texture);
}
//
gameTemp::ShaderProgram *Material::getShaderProgram()
{
    return shaderPtr;
}

void Material::setProgramUniforms()
{
    for (const auto &[key, uniform] : uniformsMap)
    {
        if (uniform.typeId == typeid(GLfloat))
        {
            shaderPtr->set(key, *(std::any_cast<GLfloat *>(uniform.data)));
            continue;
        }
        else if (uniform.typeId == typeid(GLint))
        {
            shaderPtr->set(key, *(std::any_cast<GLint *>(uniform.data)));
            continue;
        }
        else if (uniform.typeId == typeid(GLboolean))
        {
            shaderPtr->set(key, *(std::any_cast<GLboolean *>(uniform.data)));
            continue;
        }
        else if (uniform.typeId == typeid(glm::mat4))
        {
            shaderPtr->set(key, *(std::any_cast<glm::mat4 *>(uniform.data)));
            continue;
        }
        else if (uniform.typeId == typeid(glm::vec2))
        {
            shaderPtr->set(key, *(std::any_cast<glm::vec2 *>(uniform.data)));
            continue;
        }
        else if (uniform.typeId == typeid(glm::vec3))
        {
            shaderPtr->set(key, *(std::any_cast<glm::vec3 *>(uniform.data)));
            continue;
        }
        else if (uniform.typeId == typeid(glm::vec4))
        {
            shaderPtr->set(key, *(std::any_cast<glm::vec4 *>(uniform.data)));
            continue;
        }
        else if (uniform.typeId == typeid(float))
        {
            shaderPtr->set(key, *(std::any_cast<float *>(uniform.data)));
            continue;
        }
        else if (uniform.typeId == typeid(bool))
        {
            shaderPtr->set(key, *(std::any_cast<bool *>(uniform.data)));
            continue;
        }
        else if (uniform.typeId == typeid(int))
        {
            shaderPtr->set(key, *(std::any_cast<int *>(uniform.data)));
            continue;
        }
    }
}

void Material::activateUnitTextures()
{
    for (int i = 0, numTextures = unitTextures.size(); i < numTextures; i++)
    {

        int texture = unitTextures[i].texture->getTexture();
        glActiveTexture(GL_TEXTURE0 + texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        if (unitTextures[i].sampler != nullptr)
        {
            glBindSampler(texture, unitTextures[i].sampler->getSampler());
            shaderPtr->set("material." + unitTextures[i].name, texture);
        }
        else
        {
            shaderPtr->set("material." + unitTextures[i].name, texture);
        }
    }
}
void Material::setObjProp(ObjectProperties *obj)
{
    this->objProp = obj;
}

ObjectProperties *Material::getObjProp()
{
    return this->objProp;
}

Material::~Material()
{
}
// Creation From Base Fn
//shader program , objProp ptr, vector of shaders , vector of samplers
Material *Material::CreationFromBase(gameTemp::ShaderProgram *myProgram, ObjectProperties *objPtr, vector<gameTemp ::Texture *> &recTexVec, vector<gameTemp ::Sampler *> &recSamplerVec, vector<string> unitTextureNameVec)
{
    Material *matPtr = new Material(myProgram);
    matPtr->setObjProp(objPtr);
    for (int i = 0; i < recTexVec.size(); i++)
    {
        unitTexture extractedUnitTex;
        extractedUnitTex.texture = recTexVec[i];
        extractedUnitTex.sampler = recSamplerVec[i];
        extractedUnitTex.name = unitTextureNameVec[i];
        matPtr->addUnitTexture(extractedUnitTex);
    }
    return matPtr;
}
//Read Data Fn
void Material::ReadData(string inputFilePath, std::unordered_map<std::string, gameTemp::Texture *> &texMap, vector<gameTemp::Sampler *> &recSamplerVector, map<string, gameTemp::ShaderProgram> &programs, vector<Material *> &materialVec)
{
    vector<ObjectProperties *> objCreatedVector;
    //
    Json::Value data;
    std::ifstream people_file(inputFilePath, std::ifstream::binary);
    people_file >> data;
    string materialRead = "material";
    string materialReadTemp = "material";
    int numberofMaterials = data["World"]["Materials"].size();
    //
    for (int pos = 1; pos <= numberofMaterials; pos++)
    {
        ObjectProperties *objPtr;
        vector<string> texNameVector;
        vector<string> uniformNameVector;
        vector<int> samplerPosVector;
        vector<gameTemp::Texture *> filledTexVec;
        vector<gameTemp::Sampler *> filledSamplerVec;
        materialRead += to_string(pos);
        int texRefSize = data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"].size();
        string shaderName = data["World"]["Materials"][pos - 1][materialRead]["shader name"].asString();
        //Adding for this Material a vector of textures
        for (int i = 0; i < texRefSize; i++)
        {
            if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["name"].asString() == "emissive_map")
            {
                string exTexName = data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["texture ref"].asString();
                uniformNameVector.push_back("emissive_map");
                texNameVector.push_back(exTexName);
                int samplerpos;
                if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"])
                {
                    samplerpos = (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"].asInt()) - 1;
                }
                else
                {
                    samplerpos = -1;
                }
                samplerPosVector.push_back(samplerpos);
            }
            else if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["name"].asString() == "albedo_map")
            {
                string exTexName = data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["texture ref"].asString();
                uniformNameVector.push_back("albedo_map");
                texNameVector.push_back(exTexName);
                int samplerpos;
                if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"])
                {
                    samplerpos = (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"].asInt()) - 1;
                }
                else
                {
                    samplerpos = -1;
                }
                samplerPosVector.push_back(samplerpos);
            }
            else if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["name"].asString() == "specular_map")
            {
                string exTexName = data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["texture ref"].asString();
                uniformNameVector.push_back("specular_map");
                texNameVector.push_back(exTexName);
                int samplerpos;
                if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"])
                {
                    samplerpos = (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"].asInt()) - 1;
                }
                else
                {
                    samplerpos = -1;
                }
                samplerPosVector.push_back(samplerpos);
            }
            else if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["name"].asString() == "roughness_map")
            {
                string exTexName = data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["texture ref"].asString();
                uniformNameVector.push_back("roughness_map");
                texNameVector.push_back(exTexName);
                int samplerpos;
                if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"])
                {
                    samplerpos = (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"].asInt()) - 1;
                }
                else
                {
                    samplerpos = -1;
                }
                samplerPosVector.push_back(samplerpos);
            }
            else if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["name"].asString() == "ambient_occlusion_map")
            {
                string exTexName = data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["texture ref"].asString();
                uniformNameVector.push_back("ambient_occlusion_map");
                texNameVector.push_back(exTexName);
                int samplerpos;
                if (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"])
                {
                    samplerpos = (data["World"]["Materials"][pos - 1][materialRead]["textures and samplers Reference"][i]["sampler ref"].asInt()) - 1;
                }
                else
                {
                    samplerpos = -1;
                }
                samplerPosVector.push_back(samplerpos);
            }
        }
        //Extracting object Poperties
        //--if there is an object property
        if (data["World"]["Materials"][pos - 1][materialRead]["object Property"])
        {
            bool isCull = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Culling"]["enabled"].asBool();
            string faceToCull = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Culling"]["face to cull"].asString();
            string windingDirection = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Culling"]["winding direction"].asString();
            bool isBlend = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Blending"]["enabled"].asBool();
            string blendType = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Blending"]["type"].asString();
            int srcClrSize = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Blending"]["src color"].size();
            int dstClrSize = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Blending"]["dest color"].size();
            int constClrSize = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Blending"]["constClr"].size();
            //Arrs
            float srcClrArr[] = {0.0, 0.0, 0.0, 0.0};
            float dstClrArr[] = {0.0, 0.0, 0.0, 0.0};
            float constClrArr[] = {0.0, 0.0, 0.0, 0.0};
            for (int l = 0; l < srcClrSize; l++)
            {
                srcClrArr[l] = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Blending"]["src color"][l].asFloat();
            }
            for (int l = 0; l < dstClrSize; l++)
            {
                dstClrArr[l] = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Blending"]["dest color"][l].asFloat();
            }
            for (int l = 0; l < constClrSize; l++)
            {
                constClrArr[l] = data["World"]["Materials"][pos - 1][materialRead]["object Property"]["Blending"]["constClr"][l].asFloat();
            }
            glm::vec4 srcClrVec = {srcClrArr[0], srcClrArr[1], srcClrArr[2], srcClrArr[3]};
            glm::vec4 destClrVec = {dstClrArr[0], dstClrArr[1], dstClrArr[2], dstClrArr[3]};
            glm::vec4 constClrVec = {constClrArr[0], constClrArr[1], constClrArr[2], constClrArr[3]};
            objPtr = ObjectProperties::CreationFromBase(isCull, faceToCull, windingDirection, isBlend, blendType, srcClrVec, destClrVec, constClrVec);
            objCreatedVector.push_back(objPtr);
        }
        else
        {
            objCreatedVector.push_back(nullptr);
        }

        for (int p = 0; p < texNameVector.size(); p++)
        {
            filledTexVec.push_back(texMap[texNameVector[p]]);
            if (samplerPosVector[p] == -1) // texture doesnot have a sample
            {
                filledSamplerVec.push_back(nullptr);
            }
            else
            {
                filledSamplerVec.push_back(recSamplerVector[samplerPosVector[p]]);
            }
        }
        //
        materialVec.push_back(CreationFromBase(&programs[shaderName], objPtr, filledTexVec, filledSamplerVec, uniformNameVector));
        //last line
        materialRead = materialReadTemp;
    }
    cout << "MATERIAAAAALLLLL IS DOEEEEE   " << endl;
}