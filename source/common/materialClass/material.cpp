#include "./material.hpp"

int Material :: num=0;
Material::Material(gameTemp::ShaderProgram *specifiedShader)
{
    texture=-1;
    sampler=-1;
    shaderPtr = specifiedShader;
    i=num;
    num++;
}

void Material::setShaderProgram(gameTemp::ShaderProgram *specifiedShader)
{
    shaderPtr = specifiedShader;
}

void Material ::setTexture(GLuint myTex){
    this->texture = myTex;
}

void Material ::setSampler(GLuint mySamp){
    if(texture!=-1) //There is no texture
        this->sampler=mySamp;
}

void Material ::setIndex(int num1){
    num=num1;
}
int Material :: getIndex(){
    return this->i;
}

GLuint Material ::getTexture(){
    return this->texture;
}

GLuint Material :: getSampler(){
    return this->sampler;
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
