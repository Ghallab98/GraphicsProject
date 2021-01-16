#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <data-types.h>
#include <iostream>
#include <glad/gl.h>
#include <glm/vec2.hpp>
#include "../../vendor/jsoncpp/include/json/value.h"
#include "../../vendor/jsoncpp/include/json/json.h"
#include <fstream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
namespace gameTemp
{
    class Texture
    {
    private:
        GLuint texture;
        bool Active_Mipmap;
        int mipmapLevel;
        int width;
        int height;
        int unpack;
        //To be called from the Read Data fn
        static Texture *CreationFromBase(bool isLoaded, string path, bool activeMipMap = 0, int mipMapLevel = 0, int width = 0, int height = 0, int unpack = 0, glm::ivec2 size = {0, 0}, glm::ivec2 patternSize = {0, 0}, gameTemp::Color color1 = {0, 0, 0, 0}, gameTemp::Color color2 = {0, 0, 0, 0});

    public:
        void create(bool Active_Mipmap, int mipmapLevel, int width, int height, int unpack, const char *filename);

        void destroy()
        {
            glDeleteTextures(1, &this->texture);
        };

        Texture()
        {
            glGenTextures(1, &(this->texture));
        };
        ~Texture()
        {
            destroy();
        };

        GLuint getTexture() const;

        void setTexture(GLuint texture);

        glm::ivec2 loadImage(const char *filename);
        void checkerBoard(glm::ivec2 size, glm::ivec2 patternSize, gameTemp::Color color1, gameTemp::Color color2);
        void singleColor(Color color, glm::ivec2 size = {1, 1});
        Texture(Texture const &) = delete;
        Texture &operator=(Texture const &) = delete;
        //Read Data
        static void ReadData(string inputPath, unordered_map<string, Texture *> &textures);
    };

} // namespace gameTemp
#endif
