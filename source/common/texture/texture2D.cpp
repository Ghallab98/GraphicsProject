#include "texture2D.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
void gameTemp::Texture::create(bool Active_Mipmap, int mipmapLevel, int width, int height, int unpack, const char *filename)
{
    this->Active_Mipmap = Active_Mipmap;
    this->mipmapLevel = mipmapLevel;
    this->width = width;
    this->height = height;
    this->unpack = unpack;
    loadImage(filename);
}
glm::ivec2 gameTemp::Texture::loadImage(const char *filename)
{
    glm::ivec2 size;
    int channels;
    //Since OpenGL puts the texture origin at the bottom left while images typically has the origin at the top left,
    //We need to till stb to flip images vertically after loading them
    stbi_set_flip_vertically_on_load(true);
    //Load image data and retrieve width, height and number of channels in the image
    //The last argument is the number of channels we want and it can have the following values:
    //- 0: Keep number of channels the same as in the image file
    //- 1: Grayscale only
    //- 2: Grayscale and Alpha
    //- 3: RGB
    //- 4: RGB and Alpha
    //Note: channels (the 4th argument) always returns the original number of channels in the file
    unsigned char *data = stbi_load(filename, &size.x, &size.y, &channels, 4);
    if (data == nullptr)
    {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return {0, 0};
    }
    //Bind the texture such that we upload the image data to its storage
    glBindTexture(GL_TEXTURE_2D, this->texture);
    //Set Unpack Alignment to 4-byte (it means that each row takes multiple of 4 bytes in memory)
    //Note: this is not necessary since:
    //- Alignment is 4 by default
    //- Alignment of 1 or 2 will still work correctly but 8 may cause problems
    glPixelStorei(GL_UNPACK_ALIGNMENT, this->unpack);
    //Send data to texture
    //NOTE: the internal format is set to GL_RGBA8 so every pixel contains 4 bytes, one for each channel
    glTexImage2D(GL_TEXTURE_2D, this->mipmapLevel, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //Generate versions of the texture at smaller level of details (useful for filtering)
    if (this->Active_Mipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data); //Free image data after uploading to GPU
    this->width = size.x;
    this->height = size.y;
    return size;
}
void gameTemp::Texture::singleColor(gameTemp::Color color, glm::ivec2 size)
{
    //Allocate array for texture data
    auto *data = new Color[size.x * size.y];
    //Fill array with the same color
    std::fill_n(data, size.x * size.y, color);
    //Bind the texture such that we upload the image data to its storage
    glBindTexture(GL_TEXTURE_2D, this->texture);
    //Set Unpack Alignment to 4-byte (it means that each row takes multiple of 4 bytes in memory)
    //Note: this is not necessary since:
    //- Alignment is 4 by default
    //- Alignment of 1 or 2 will still work correctly but 8 will cause problems
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    //Send data to texture
    //NOTE: the internal format is set to GL_RGBA8 so every pixel contains 4 bytes, one for each channel
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //Generate Mipmaps after loading the texture
    glGenerateMipmap(GL_TEXTURE_2D);
    delete[] data;
}

void gameTemp::Texture::checkerBoard(glm::ivec2 size, glm::ivec2 patternSize, gameTemp::Color color1, gameTemp::Color color2)
{
    auto *data = new gameTemp::Color[size.x * size.y];
    int ptr = 0;
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            data[ptr++] = ((x / patternSize.x) & 1) ^ ((y / patternSize.y) & 1) ? color1 : color2;
        }
    }
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    delete[] data;
}
GLuint gameTemp::Texture::getTexture() const
{
    return this->texture;
}

void gameTemp::Texture::setTexture(GLuint texture)
{
    this->texture = texture;
}

//Creation From Base FN
gameTemp::Texture *gameTemp::Texture::CreationFromBase(bool isLoaded, string path, bool activeMipMap, int mipMapLevel, int width, int height, int unpack, glm::ivec2 size, glm::ivec2 patternSize, gameTemp::Color color1, gameTemp::Color color2)
{
    gameTemp::Texture *myTexturePtr = new gameTemp::Texture();
    if (isLoaded)
    {
        myTexturePtr->create(activeMipMap, mipMapLevel, width, height, unpack, path.c_str());
    }
    else
    {
        myTexturePtr->checkerBoard(size, patternSize, color1, color2);
    }
    return myTexturePtr;
}

//Read FN
void gameTemp::Texture::ReadData(string inputPath, unordered_map<string, gameTemp::Texture *> &textures)
{
    Json::Value data;
    std::ifstream people_file(inputPath, std::ifstream::binary);
    people_file >> data;
    string textureRead = "texture";
    string textureReadTemp = "texture";
    int numberofTextures = data["Resources"]["Textures"].size();
    for (int pos = 1; pos <= numberofTextures; pos++)
    {
        textureRead += to_string(pos);
        bool isLoaded = data["Resources"]["Textures"][pos - 1][textureRead]["isLoaded"].asBool();
        string textureName = data["Resources"]["Textures"][pos - 1][textureRead]["name"].asString();
        if (isLoaded)
        {
            string texturePath = data["Resources"]["Textures"][pos - 1][textureRead]["path"].asString();
            //Defualt values in case not given in json file
            bool activeMipMap = true;
            int mipMapLevel = 0;
            int width = 256;
            int height = 128;
            int unpack = 0;
            if (data["Resources"]["Textures"][pos - 1][textureRead]["active_MipMap"])
            {
                activeMipMap = data["Resources"]["Textures"][pos - 1][textureRead]["active_MipMap"].asBool();
            }

            if (data["Resources"]["Textures"][pos - 1][textureRead]["mipMapLevel"])
            {
                mipMapLevel = data["Resources"]["Textures"][pos - 1][textureRead]["mipMapLevel"].asInt();
            }
            if (data["Resources"]["Textures"][pos - 1][textureRead]["width"])
            {
                width = data["Resources"]["Textures"][pos - 1][textureRead]["width"].asInt();
            }
            if (data["Resources"]["Textures"][pos - 1][textureRead]["height"])
            {
                height = data["Resources"]["Textures"][pos - 1][textureRead]["height"].asInt();
            }
            if (data["Resources"]["Textures"][pos - 1][textureRead]["unPack"])
            {
                unpack = data["Resources"]["Textures"][pos - 1][textureRead]["unPack"].asInt();
            }
            //textures[textureName] = CreationFromBase(isLoaded);
            //Save in the textures Map
            textures[textureName] = CreationFromBase(isLoaded, texturePath, activeMipMap, mipMapLevel, width, height, unpack, {0, 0}, {0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0});
        }
        else
        {
            int size[2];
            int patternSize[2];
            int color1[4];
            int color2[4];
            //Fill Size and Pattern size
            for (int i = 0; i < 2; i++)
            {
                size[i] = data["Resources"]["Textures"][pos - 1][textureRead]["size"][i].asInt();
                patternSize[i] = data["Resources"]["Textures"][pos - 1][textureRead]["patternSize"][i].asInt();
            }
            //Fill Color1 and Color2
            for (int j = 0; j < 4; j++)
            {
                color1[j] = data["Resources"]["Textures"][pos - 1][textureRead]["color1"][j].asInt();
                color2[j] = data["Resources"]["Textures"][pos - 1][textureRead]["color2"][j].asInt();
            }
            //Save in the textures Map
            textures[textureName] = CreationFromBase(isLoaded, " ", 0, 0, 0, 0, 0, {size[0], size[1]}, {patternSize[0], patternSize[1]}, {color1[0], color1[1], color1[2], color1[3]}, {color2[0], color2[1], color2[2], color2[3]});
        }
        //last line
        textureRead = textureReadTemp;
    }
}