#include "./material.hpp"

Material::Material(gameTemp::ShaderProgram *specifiedShader)
{
    shaderPtr = specifiedShader;
}

void Material::setShaderProgram(gameTemp::ShaderProgram *specifiedShader)
{
    shaderPtr = specifiedShader;
}

gameTemp::ShaderProgram *Material::getShaderProgram()
{
    return shaderPtr;
}

map<uniformType, any> Material::GetUniformsMap()
{
    return this->uniformsMap;
}

void Material::setObjProp(ObjectProperties *obj)
{
    this->objProp = obj;
}

ObjectProperties *Material::getObjProp()
{
    return this->objProp;
}

glm::vec4 *Material::getTint()
{
    auto tintUniform = uniformsMap.find(tint);
    if (tintUniform == uniformsMap.end())
        return nullptr;

    return std::any_cast<glm::vec4 *>(tintUniform->second);
}

Material::~Material()
{
}
