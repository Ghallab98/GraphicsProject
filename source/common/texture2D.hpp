#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <data-types.h>
#include <iostream>
#include <string>
#include <glad/gl.h>
#include <glm/vec2.hpp>

namespace gameTemp {
    class Texture {
    private:
        GLuint texture = -1;
        //enum textureType;
        bool Active_Mipmap;
        int mipmapLevel;
        int width;
        int height;
        int unpack;
    public :
        void create(bool Active_Mipmap,int mipmapLevel,int width, int height,int unpack,const char *filename);

        void destroy() {
            glDeleteTextures(1, &this->texture);
        };

        Texture(){
            glGenTextures(1, &(this->texture));
        };
        ~Texture(){
            destroy();
        };

        GLuint getTexture() const;

        void setTexture(GLuint texture);

        glm::ivec2 loadImage(const char* filename);
        void checkerBoard(GLuint texture, glm::ivec2 size, glm::ivec2 patternSize, gameTemp::Color color1, gameTemp::Color color2);
        Texture(Texture const &) = delete;
        Texture &operator=(Texture const &) = delete;
    };

}
#endif 
