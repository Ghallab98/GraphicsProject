// Material class stores
// 1- pointer to the shader (fragment shader)
// 2- map of uniforms that will be sent to the shader
// 3- rendrer state  (SAVED IN ENTITY DIRECLTY FOR NOW)

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <map>
#include <any>
#include <typeinfo>
#include <shader.hpp>
#include <vector>
#include "./objectProperties.cpp"
#include "../texture/texture2D.hpp"
#include "../sampler.hpp"

using gameTemp::Sampler;
using gameTemp::ShaderProgram;
using gameTemp::Texture;
using std::any;
using std::map;
using std::string;
using std::vector;
//
struct uniform
{
    any data;
    const type_info &typeId;
};

struct unitTexture
{
    Texture *texture = nullptr;
    Sampler *sampler = nullptr;
    string name;
};
//
class Material
{
private:
    ObjectProperties *objProp;
    gameTemp::ShaderProgram *shaderPtr;
    map<std::string, uniform> uniformsMap;
    vector<unitTexture> unitTextures;
    //Creation from base function
    static Material *CreationFromBase(gameTemp::ShaderProgram *myProgram, ObjectProperties *objPtr, vector<gameTemp ::Texture *> &recTexVec, vector<gameTemp ::Sampler *> &recSamplerVec, vector<string> unitTextureNameVec);

public:
    Material(gameTemp::ShaderProgram *specifiedShader);

    void setShaderProgram(gameTemp::ShaderProgram *specifiedShader);
    void setObjProp(ObjectProperties *obj);
    void addUnitTexture(unitTexture unit_texture);

    template <class T>
    void AddUniform(std::string name, T *value);

    gameTemp::ShaderProgram *getShaderProgram();
    ObjectProperties *getObjProp();

    void setProgramUniforms();
    void activateUnitTextures();

    //Read Data function
    static void ReadData(string inputFilePath, std::unordered_map<std::string, gameTemp::Texture *> &texMap, vector<gameTemp::Sampler *> &recSamplerVector, map<string, gameTemp::ShaderProgram> &programs, vector<Material *> &materialVec);
    ~Material();
};

template <class T>
void Material::AddUniform(std::string name, T *value)
{
    this->uniformsMap.insert(std::pair<std::string, struct uniform>(name, {value, typeid(T)}));
}

#endif