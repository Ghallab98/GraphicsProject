//
// Created by Karim on 12/20/2020.
//
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
        GLuint sampler;
        GLenum magnification_filter = GL_LINEAR;
        GLenum minification_filter = GL_LINEAR_MIPMAP_LINEAR;
        GLenum wrap_s = GL_REPEAT;
        GLenum wrap_t = GL_REPEAT;
        GLfloat anisotropy = 1.0f;
        bool max_anisotropy =true ;
        glm::vec4 border_color = {0,0,0,1};
    public:
        void create(GLuint sampler,GLenum magnification_filter ,GLenum minification_filter,GLenum wrap_s,GLenum wrap_t,bool max_anisotropy,GLfloat anistropy,glm::vec4 border_color);
        void destroy() {glDeleteSamplers(1, &this->sampler);};

        Sampler(){glGenSamplers(1, &this->sampler);};
        ~Sampler(){ destroy(); }

        GLuint getSampler() const;

        //Delete copy constructor and assignment operation
        //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
        //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
        Sampler(Sampler const &) = delete;
        Sampler &operator=(Sampler const &) = delete;
    };
}

#endif
