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

#include "./uniformType.hpp"
#include "./objectProperties.cpp"

using std::any;
using std::map;

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
    GLuint texture;
    GLuint sampler;

public:
    Material(gameTemp::ShaderProgram *specifiedShader);

    void setShaderProgram(gameTemp::ShaderProgram *specifiedShader);
    void setObjProp(ObjectProperties *obj);
    void setTexture(GLuint myTex);
    void setSampler(GLuint mySamp);
    static void setIndex(int num1);

    template <class T>
    void AddUniform(std::string name, T *value);

    gameTemp::ShaderProgram *getShaderProgram();
    ObjectProperties *getObjProp();
    GLuint getTexture();
    GLuint getSampler();
    int getIndex();

    void setProgramUniforms();

    ~Material();
};

template <class T>
void Material::AddUniform(std::string name, T *value)
{
    this->uniformsMap.insert(std::pair<std::string, struct uniform>(name, {value, typeid(T)}));
}

#endif