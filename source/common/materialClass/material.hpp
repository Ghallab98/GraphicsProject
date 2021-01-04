// Material class stores
// 1- pointer to the shader (fragment shader)
// 2- map of uniforms that will be sent to the shader
// 3- rendrer state  (SAVED IN ENTITY DIRECLTY FOR NOW)
// 4- GLuint for texture 

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
    static int num;
    int i;
    ObjectProperties *objProp;
    gameTemp::ShaderProgram *shaderPtr;
    map<uniformType, any> uniformsMap;
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
    void AddUniform(uniformType type, T *value);

    gameTemp::ShaderProgram *getShaderProgram();
    map<uniformType, std::any> GetUniformsMap();
    ObjectProperties *getObjProp();
    GLuint getTexture();
    GLuint getSampler();
    int getIndex();
    
    glm::vec4 *getTint();

    ~Material();
};

template <class T>
void Material::AddUniform(uniformType type, T *value)
{
    this->uniformsMap.insert(std::pair<uniformType, T *>(type, value));
}

#endif