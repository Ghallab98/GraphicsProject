#include"./material.hpp"

Material:: Material(gameTemp::ShaderProgram *specifiedShader) 
{
    shaderPtr = specifiedShader;
}
void  Material:: setShaderProgram(gameTemp::ShaderProgram *specifiedShader)
{
    shaderPtr = specifiedShader;
}
gameTemp::ShaderProgram *  Material:: getShaderProgram()
{
    return shaderPtr;
}

void  Material:: AddUniform(Uniform<std::any>* newUniform)
{
    this->uniformsMap.insert(std::pair<uniformType, std::any>(newUniform->getUniformtype(), newUniform->getUniformValue()));
}

map<std::string, std::any> Material::  GetUniformsMap()
{
    return this->uniformsMap;
}

void Material:: setObjProp(ObjectProperties * obj)
{
    this->objProp=obj;
}
ObjectProperties *Material::getObjProp()
{
    return this->objProp;
}

Material:: ~Material()
{
}
