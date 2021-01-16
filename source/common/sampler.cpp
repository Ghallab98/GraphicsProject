#include "sampler.hpp"

void gameTemp::Sampler::setWrapT(GLenum myWrapT)
{
    this->wrap_t = myWrapT;
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_T, this->wrap_t);
}
void gameTemp::Sampler::setWrapS(GLenum myWrapS)
{
    this->wrap_s = myWrapS;
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_S, this->wrap_s);
}
void gameTemp::Sampler::setAnisotropy(GLfloat anisotropy)
{
    this->anisotropy = anisotropy;
    glSamplerParameterf(this->sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, this->anisotropy);
}
void gameTemp::Sampler::setMaxAnisotropy(bool max_anisotropy)
{
    this->max_anisotropy = max_anisotropy;
}
void gameTemp::Sampler::setBorderColor(glm::vec4 border_color)
{
    this->border_color = border_color;
    glSamplerParameterfv(this->sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(this->border_color));
}
void gameTemp::Sampler::setMagnificationFilter(GLenum magnification_filter)
{
    this->magnification_filter = magnification_filter;
    glSamplerParameteri(this->sampler, GL_TEXTURE_MAG_FILTER, this->magnification_filter);
}
void gameTemp::Sampler::setMinificationFilter(GLenum minification_filter)
{
    this->minification_filter = minification_filter;
    glSamplerParameteri(this->sampler, GL_TEXTURE_MIN_FILTER, this->minification_filter);
}
GLuint gameTemp::Sampler::getSampler() const
{
    return this->sampler;
}

void gameTemp::Sampler::create(GLenum wrap_t, GLenum magnification_filter, GLenum minification_filter, GLenum wrap_s,
                               bool max_anisotropy, GLfloat anistropy, glm::vec4 border_color)
{
    this->magnification_filter = magnification_filter;
    this->minification_filter = minification_filter;
    this->wrap_s = wrap_s;
    this->wrap_t = wrap_t;
    this->max_anisotropy = max_anisotropy;
    this->border_color = border_color;

    if (this->max_anisotropy)
    {
        GLfloat max_anisotropy_upper_bound;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy_upper_bound);
        this->anisotropy = max_anisotropy_upper_bound;
    }
    else
    {
        this->anisotropy = anistropy;
    }
    //std::cout <<this->wrap_t <<std::endl;
    glSamplerParameteri(this->sampler, GL_TEXTURE_MAG_FILTER, this->magnification_filter);
    glSamplerParameteri(this->sampler, GL_TEXTURE_MIN_FILTER, this->minification_filter);
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_S, this->wrap_s);
    glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_T, this->wrap_t);
    glSamplerParameterfv(this->sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(this->border_color));
    glSamplerParameterf(this->sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, this->anisotropy);
}

//Creation From Base fn
gameTemp::Sampler *gameTemp::Sampler::CreationFromBase(GLenum wrap_s, GLenum magnification_filter, GLenum minification_filter, GLenum wrap_t, bool max_anisotropy, GLfloat anistropy, glm::vec4 border_color)
{
    gameTemp::Sampler *samplerPtr = new gameTemp::Sampler();
    samplerPtr->create(wrap_s, magnification_filter, minification_filter, wrap_t, max_anisotropy, anistropy, border_color);
    return samplerPtr;
}

//Read Data fn
void gameTemp::Sampler::ReadData(string inputPath, vector<gameTemp::Sampler *> &sampVec)
{
    Json::Value data;
    std::ifstream people_file(inputPath, std::ifstream::binary);
    people_file >> data;
    string samplerRead = "sampler";
    string samplerReadTemp = "sampler";
    int numberofSamplers = data["Resources"]["Samplers"].size();
    //
    for (int pos = 1; pos <= numberofSamplers; pos++)
    {
        samplerRead += to_string(pos);
        unsigned int magnificationValueRead = GL_LINEAR;
        unsigned int minificationValueRead = GL_LINEAR_MIPMAP_LINEAR;
        unsigned int wraptRead = GL_REPEAT;
        unsigned int wrapsRead = GL_REPEAT;
        bool mxantsRead = true;
        float ansistropy = 1.0;
        float borderColorRead[4] = {0.0, 0.0, 0.0, 1.0};
        if (data["Resources"]["Samplers"][pos - 1][samplerRead]["magnification"])
        {
            string magnificationS = data["Resources"]["Samplers"][pos - 1][samplerRead]["magnification"].asString();
            std::istringstream converter(magnificationS);
            converter >> std::hex >> magnificationValueRead;
            //cout << "magnification  is present  " << magnificationValueRead << endl;
        }
        if (data["Resources"]["Samplers"][pos - 1][samplerRead]["minification"])
        {
            string minificationS = data["Resources"]["Samplers"][pos - 1][samplerRead]["minification"].asString();
            std::istringstream converter(minificationS);
            converter >> std::hex >> minificationValueRead;
            //cout << "minification  is present  " << minificationValueRead << endl;
        }
        if (data["Resources"]["Samplers"][pos - 1][samplerRead]["wrapt"])
        {
            string wrapTS = data["Resources"]["Samplers"][pos - 1][samplerRead]["wrapt"].asString();
            std::istringstream converter(wrapTS);
            converter >> std::hex >> wraptRead;
            //cout << "wrapt  is present  " << wraptRead << endl;
        }
        if (data["Resources"]["Samplers"][pos - 1][samplerRead]["wraps"])
        {
            string wrapSS = data["Resources"]["Samplers"][pos - 1][samplerRead]["wraps"].asString();
            std::istringstream converter(wrapSS);
            converter >> std::hex >> wrapsRead;
            //cout << "wraps  is present  " << wrapsRead << endl;
        }
        if (data["Resources"]["Samplers"][pos - 1][samplerRead]["max_anisotropy"])
        {
            mxantsRead = data["Resources"]["Samplers"][pos - 1][samplerRead]["max_anisotropy"].asBool();
            //cout << "max_anisotropy  is present  " << mxantsRead << endl;
        }
        if (data["Resources"]["Samplers"][pos - 1][samplerRead]["anistropy"])
        {
            ansistropy = data["Resources"]["Samplers"][pos - 1][samplerRead]["anistropy"].asFloat();
            //cout << "anistropy  is present  " << ansistropy << endl;
        }
        if (data["Resources"]["Samplers"][pos - 1][samplerRead]["border_color"])
        {
            borderColorRead[0] = data["Resources"]["Samplers"][pos - 1][samplerRead]["border_color"][0].asFloat();
            borderColorRead[1] = data["Resources"]["Samplers"][pos - 1][samplerRead]["border_color"][1].asFloat();
            borderColorRead[2] = data["Resources"]["Samplers"][pos - 1][samplerRead]["border_color"][2].asFloat();
            borderColorRead[3] = data["Resources"]["Samplers"][pos - 1][samplerRead]["border_color"][3].asFloat();
            //cout << "border_color  is present  " << borderColorRead[0] << borderColorRead[1] << borderColorRead[2] << borderColorRead[3] << endl;
        }

        sampVec.push_back(CreationFromBase(wrapsRead, magnificationValueRead, minificationValueRead, wraptRead, mxantsRead, ansistropy, glm::vec4(borderColorRead[0], borderColorRead[1], borderColorRead[2], borderColorRead[3])));
        //last line
        samplerRead = samplerReadTemp;
    }
}