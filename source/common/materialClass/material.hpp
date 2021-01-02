// Material class stores
// 1- pointer to the shader (fragment shader)
// 2- map of uniforms that will be sent to the shader
// 3- rendrer state  (SAVED IN ENTITY DIRECLTY FOR NOW)

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <map>
#include <any>
#include <shader.hpp>

#include "./uniformType.hpp"
#include "./objectProperties.cpp"

using std::any;
using std::map;

class Material
{
private:
    ObjectProperties *objProp;
    gameTemp::ShaderProgram *shaderPtr;
    map<uniformType, any> uniformsMap;

public:
    Material(gameTemp::ShaderProgram *specifiedShader);

    void setShaderProgram(gameTemp::ShaderProgram *specifiedShader);
    void setObjProp(ObjectProperties *obj);

    template <class T>
    void AddUniform(uniformType type, T *value);

    gameTemp::ShaderProgram *getShaderProgram();
    map<uniformType, std::any> GetUniformsMap();
    ObjectProperties *getObjProp();
    glm::vec4 *getTint();

    ~Material();
};

template <class T>
void Material::AddUniform(uniformType type, T *value)
{
    this->uniformsMap.insert(std::pair<uniformType, T *>(type, value));
}

#endif