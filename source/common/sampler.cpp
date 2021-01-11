#include "sampler.hpp"

void gameTemp::Sampler:: setWrapT(GLenum myWrapT){
    this->wrap_t=myWrapT;
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_T, this->wrap_t);
}
void gameTemp::Sampler::setWrapS(GLenum myWrapS){
    this->wrap_s=myWrapS;
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_S, this->wrap_s);
}
void gameTemp::Sampler::setAnisotropy(GLfloat anisotropy){
    this->anisotropy = anisotropy;
    glSamplerParameterf(this->sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, this->anisotropy);
}
void gameTemp::Sampler::setMaxAnisotropy(bool max_anisotropy){
    this->max_anisotropy = max_anisotropy;
}
void gameTemp::Sampler::setBorderColor(glm::vec4 border_color){
    this->border_color = border_color;
    glSamplerParameterfv(this->sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(this->border_color));
}
void gameTemp::Sampler::setMagnificationFilter(GLenum magnification_filter){
    this->magnification_filter = magnification_filter;
    glSamplerParameteri(this->sampler, GL_TEXTURE_MAG_FILTER, this->magnification_filter);
}
void gameTemp::Sampler::setMinificationFilter(GLenum minification_filter){
    this->minification_filter = minification_filter;
    glSamplerParameteri(this->sampler, GL_TEXTURE_MIN_FILTER, this->minification_filter);
}
GLuint gameTemp::Sampler::getSampler() const {
    return this->sampler;
}

void gameTemp::Sampler::create(GLenum wrap_t, GLenum magnification_filter, GLenum minification_filter, GLenum wrap_s,
                                bool max_anisotropy,GLfloat anistropy ,glm::vec4 border_color) {
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
    //std::cout <<this->wrap_t <<std::endl;
    glSamplerParameteri(this->sampler, GL_TEXTURE_MAG_FILTER, this->magnification_filter);
    glSamplerParameteri(this->sampler, GL_TEXTURE_MIN_FILTER, this->minification_filter);
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_S, this->wrap_s);
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_T, this->wrap_t);
    glSamplerParameterfv(this->sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(this->border_color));
    glSamplerParameterf(this->sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, this->anisotropy);


}
