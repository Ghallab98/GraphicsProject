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
#include "../texture2D.hpp"
#include "../sampler.hpp"
using std::any;
using std::map;
using std::vector;
struct uniform
{
    any data;
    const type_info &typeId;
};

class Material
{
private:
    static int num;
    int i;
    ObjectProperties *objProp;
    gameTemp::ShaderProgram *shaderPtr;
    map<std::string, uniform> uniformsMap;
    vector<gameTemp::Texture *> texture;
    vector<gameTemp::Sampler *> sampler;
    //Creation from base function
    static Material *CreationFromBase(gameTemp::ShaderProgram *myProgram, ObjectProperties *objPtr, vector<gameTemp ::Texture *> &recTexVec, vector<gameTemp ::Sampler *> &recSamplerVec);

public:
    Material(gameTemp::ShaderProgram *specifiedShader);

    void setShaderProgram(gameTemp::ShaderProgram *specifiedShader);
    void setObjProp(ObjectProperties *obj);
    void addTexture(gameTemp::Texture *texture);
    void addSampler(gameTemp::Sampler *sampler = nullptr);
    static void setIndex(int num1);

    template <class T>
    void AddUniform(std::string name, T *value);

    gameTemp::ShaderProgram *getShaderProgram();
    ObjectProperties *getObjProp();
    vector<gameTemp::Texture *> getTexture();
    vector<gameTemp::Sampler *> getSampler();
    int getIndex();

    void setProgramUniforms();

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