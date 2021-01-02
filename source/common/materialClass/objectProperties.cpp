#include <glm/glm.hpp>

enum FacetoCull {FRONT , BACK , TOP , BOTTOM , RIGHT, LEFT};
enum WindingDirection {CCW,CW};
enum BlendingType {Constant , NotConstant};

struct Culling {
    bool enabled = false;
    FacetoCull cullFace;   //1 front 2 back 3 top 4 bottom 5 right 6 left   TO BE REVIEWED IF AN ARRAY
    WindingDirection direction ; 
};

struct Blending{
    bool enabled=false;   
    BlendingType type= Constant;  //defualt is constant
    glm::vec4 srcClr; 
    glm::vec4 destClr;  
    glm::vec4  constClr ; //color given to the pixel 
};


class ObjectProperties{
    private:
    Culling cull;
    Blending blend;
    public:
    void setCullObjProp(Culling *myCull){
        this->cull = *myCull;
    }
    void setBlendObjProp(Blending *myBlend){
          this->blend = *myBlend;
    }
    Blending * getBlend(){
        return &(this->blend);
    }
    Culling * getCull(){
        return &(this->cull);
    }

};