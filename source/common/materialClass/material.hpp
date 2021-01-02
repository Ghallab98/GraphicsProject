//material class stores
// 1- pointer to the shader (fragment shader)
// 2-map of uniforms that will be sent to the shader
// 3- rendrer state  (SAVED IN ENTITY DIRECLTY FOR NOW)
#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <map>
#include <shader.hpp>

#include "./../uniformsTemplateClass.cpp"
#include"./objectProperties.cpp"
#include <any>
//template <class T>

class Material{
private:
    ObjectProperties * objProp;
    gameTemp::ShaderProgram *shaderPtr;
    map<uniformType, std::any> uniformsMap;
public:
    Material(gameTemp::ShaderProgram *specifiedShader) ;
    void setShaderProgram(gameTemp::ShaderProgram *specifiedShader);
    gameTemp::ShaderProgram* getShaderProgram();
    void AddUniform(Uniform<std::any>* newUniform);
    map<std::string, std::any> GetUniformsMap();
    //Obj Property setter and getter
    void setObjProp(ObjectProperties * obj);
    ObjectProperties * getObjProp();
     ~Material();
};
#endif