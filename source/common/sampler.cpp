//
// Created by Karim on 12/20/2020.
//

#include "sampler.hpp"



GLuint gameTemp::Sampler::getSampler() const {
    return this->sampler;
}

void gameTemp::Sampler::create(GLuint sampler, GLenum magnification_filter, GLenum minification_filter, GLenum wrap_s,
                               GLenum wrap_t, bool max_anisotropy,GLfloat anistropy ,glm::vec4 border_color) {


    this->sampler = sampler;
    this->magnification_filter = magnification_filter;
    this->minification_filter = minification_filter;
    this->wrap_s=wrap_s;
    this->wrap_t=wrap_t;
    this->max_anisotropy = max_anisotropy;
    this->border_color=border_color;
    if(this->max_anisotropy)
    {
        GLfloat max_anisotropy_upper_bound;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy_upper_bound);
        this->anisotropy = max_anisotropy_upper_bound;
    }
    else
    {
        this->anisotropy= anistropy;
    }

    glSamplerParameteri(this->sampler, GL_TEXTURE_MAG_FILTER, this->magnification_filter);
    glSamplerParameteri(this->sampler, GL_TEXTURE_MIN_FILTER, this->minification_filter);
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_S, this->wrap_s);
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_T, this->wrap_t);
    glSamplerParameterfv(this->sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(this->border_color));
    glSamplerParameterf(this->sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, this->anisotropy);


}

void gameTemp::Sampler::bindSampler(int textureUnit)  {
    glBindSampler(textureUnit,this->sampler);

}
