#include "./material.hpp"

int Material ::num = 0;
Material::Material(gameTemp::ShaderProgram *specifiedShader)
{
    shaderPtr = specifiedShader;
    i = num;
    num++;
}

void Material::setShaderProgram(gameTemp::ShaderProgram *specifiedShader)
{
    shaderPtr = specifiedShader;
}

void Material ::setTexture(gameTemp::Texture* texture)
{
    this->texture = texture;
}

void Material ::setSampler(gameTemp::Sampler* sampler)
{
    if (texture != nullptr) //There is no texture
        this->sampler = sampler;
}

void Material ::setIndex(int num1)
{
    num = num1;
}

int Material ::getIndex()
{
    return this->i;
}

gameTemp::Texture* Material ::getTexture()
{
    return this->texture;
}

gameTemp::Sampler* Material ::getSampler()
{
    return this->sampler;
}

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
