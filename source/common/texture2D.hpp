//
// Created by Karim on 12/20/2020.
//

#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <iostream>
#include <string>
#include <glad/gl.h>
#include <glm/vec2.hpp>

namespace gameTemp {
    class Texture {
    private:
        GLuint texture;
        //enum textureType;
        bool Active_Mipmap;
        int mipmapLevel;
        int width;
        int height;
        int unpack;
    public :
        void create(GLuint texture,const char *filename,bool Active_Mipmap = true ,int mipmapLevel = 0,int unpack = 4);
        void create(GLuint texture,bool Active_Mipmap,int mipmapLevel,int width, int height,int unpack,uint8_t *pixel_data);

        void destroy() {glDeleteTextures(1, &this->texture);};

        Texture(){glGenTextures(1, &this->texture);};
        ~Texture(){ destroy(); }

        GLuint getTexture() const;

        glm::ivec2 loadImage(const char* filename);
        void bindTexture ()
        {
            glBindTexture(GL_TEXTURE_2D, this->texture);
        }
        //Delete copy constructor and assignment operation
        //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
        //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
        Texture(Texture const &) = delete;
        Texture &operator=(Texture const &) = delete;
    };

}
#endif //GFX_LAB_TEXTURE2D_HPP
