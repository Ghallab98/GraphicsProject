#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <iostream>
#include <string>
#include <glad/gl.h>
#include <glm/vec2.hpp>
#include<glm/vec4.hpp>
#include <data-types.h>
#include <glm/gtc/type_ptr.hpp>



namespace gameTemp {
    class Sampler {
    private:
        GLuint sampler = -1;
        GLenum magnification_filter = GL_LINEAR;
        GLenum minification_filter = GL_LINEAR_MIPMAP_LINEAR;
        GLenum wrap_s = GL_REPEAT;
        GLenum wrap_t = GL_REPEAT;
        GLfloat anisotropy = 1.0f;
        bool max_anisotropy =true;
        glm::vec4 border_color = {0,0,0,1};
    public:
        void create(GLenum wrap_s=GL_REPEAT ,GLenum magnification_filter=GL_LINEAR, GLenum minification_filter=GL_LINEAR_MIPMAP_LINEAR
        , GLenum wrap_t=GL_REPEAT, bool max_anisotropy=true,GLfloat anistropy= 1.0f ,glm::vec4 border_color={0,0,0,1});
        void destroy() {
           glDeleteSamplers(1, &this->sampler);
        };

        Sampler(){glGenSamplers(1, &(this->sampler));};
        ~Sampler(){destroy(); };

        void setWrapT(GLenum myWrapT);
        void setWrapS(GLenum myWrapS);
        void setAnisotropy(GLfloat anisotropy);
        void setMaxAnisotropy(bool max_anisotropy);
        void setBorderColor(glm::vec4 border_color);
        void setMagnificationFilter(GLenum magnification_filter);
        void setMinificationFilter(GLenum minification_filter);
        GLuint getSampler() const;
        Sampler(Sampler const &) = delete;
        Sampler &operator=(Sampler const &) = delete;
    };
}

#endif
