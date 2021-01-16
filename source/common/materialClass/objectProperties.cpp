#include <glm/glm.hpp>
#include <string.h>
using namespace std;

enum FacetoCull
{
    FRONT,
    BACK,
};
enum WindingDirection
{
    CCW,
    CW
};
enum BlendingType
{
    Constant,
    NotConstant
};

struct Culling
{
    bool enabled = false;
    FacetoCull cullFace; //1 front 2 back 3 top 4 bottom 5 right 6 left   TO BE REVIEWED IF AN ARRAY
    WindingDirection direction;
};

struct Blending
{
    bool enabled = false;
    BlendingType type = Constant; //defualt is constant
    glm::vec4 srcClr;
    glm::vec4 destClr;
    glm::vec4 constClr; //color given to the pixel
};

class ObjectProperties
{
private:
    Culling cull;
    Blending blend;

public:
    ObjectProperties(bool cullEnabled, FacetoCull sentCullFace, WindingDirection sentDirection, bool blendEnabled, BlendingType SentType, glm::vec4 sentSrcClr, glm::vec4 sendestClr, glm::vec4 sentConstClr)
    {
        this->setCullObjProp(cullEnabled, sentCullFace, sentDirection);
        this->setBlendObjProp(blendEnabled, SentType, sentSrcClr, sendestClr, sentConstClr);
    };
    void setCullObjProp(bool cullEnabled, FacetoCull sentCullFace, WindingDirection sentDirection)
    {
        this->cull.enabled = cullEnabled;
        this->cull.cullFace = sentCullFace;
        this->cull.direction = sentDirection;
    }
    void setBlendObjProp(bool blendEnabled, BlendingType SentType, glm::vec4 sentSrcClr, glm::vec4 sendestClr, glm::vec4 sentConstClr)
    {
        this->blend.enabled = blendEnabled;
        this->blend.type = SentType;
        this->blend.srcClr = sentSrcClr;
        this->blend.destClr = sendestClr;
        this->blend.constClr = sentConstClr;
    }
    Blending *getBlend()
    {
        return &(this->blend);
    }
    Culling *getCull()
    {
        return &(this->cull);
    }

    //Creation From Base
    static ObjectProperties *CreationFromBase(bool cullEnabled, std::string sentCullFace, std::string sentDirection, bool blendEnabled, std::string SentType, glm::vec4 sentSrcClr, glm::vec4 sendestClr, glm::vec4 sentConstClr)
    {
        FacetoCull fc = BACK;
        WindingDirection wd = CCW;
        BlendingType bt = Constant;
        if (sentCullFace == "FRONT")
            fc = FRONT;
        if (sentDirection == "CW")
            wd = CW;
        if (SentType == "Not-Constant")
            bt = NotConstant;

        ObjectProperties *objPtr = new ObjectProperties(cullEnabled, fc, wd, blendEnabled, bt, sentSrcClr, sendestClr, sentConstClr);
        return objPtr;
    }
};