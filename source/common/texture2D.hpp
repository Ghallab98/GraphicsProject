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
        void create(GLuint texture,bool Active_Mipmap,int mipmapLevel,int width, int height,int unpack,const char *filename);

        void destroy() {
            glDeleteTextures(1, &this->texture);
        };

        Texture(){
            glGenTextures(1, &(this->texture));
        };
        ~Texture(){};

        GLuint getTexture() const;

        void setTexture(GLuint texture);

        glm::ivec2 loadImage(const char* filename);
    };

}
#endif 
